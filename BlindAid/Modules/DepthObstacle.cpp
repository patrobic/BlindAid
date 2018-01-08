#include "DepthObstacle.h"
#include "DepthObstacleFixedRegions.h"
#include "DepthObstacleHandPosition.h"

using namespace std;
using namespace cv;

namespace Vision
{
  namespace DepthObstacle
  {
    Base *Base::MakeDepthObstacle(IParameters *params, IData *input, IData *output)
    {
      if (((DepthObstacle::Parameters*)params)->GetMode() == Parameters::Mode::FixedRegions)
        return new FixedRegions::FixedRegions(params, input, output);
      else
        return new HandPosition::HandPosition(params, input, output);
    }

    Base::Base(IParameters *params, IData *input, IData *output) : IDetect(params, input, output)
    {
      _output->SetHandPosition(_params->GetDefaultCenter());
    }

    void Base::MaskShadows()
    {
      inRange(*_input->GetDepthImage(), _params->GetMinimumDistance(), _params->GetMaximumDistance(), _maskImage);
    }

    void Base::SeparateRegions()
    {
      Point tl;
      Point br;

      for (int i = 0; i < _params->GetVerticalRegions(); ++i)
        for (int j = 0; j < _params->GetHorizontalRegions(); ++j)
        {
          tl.x = _output->GetHandPosition().x + (int)((i - 2.5) * _input->GetDepthImage()->cols * _params->GetRegionWidth() * _params->GetHorizontalCoverage());
          br.x = _output->GetHandPosition().x + (int)((i - 1.5) * _input->GetDepthImage()->cols * _params->GetRegionWidth() * _params->GetHorizontalCoverage());
          tl.y = _output->GetHandPosition().y + (int)((j - 1.5) * _input->GetDepthImage()->rows * _params->GetRegionHeight() * _params->GetVerticalCoverage());
          br.y = _output->GetHandPosition().y + (int)((j - 0.5) * _input->GetDepthImage()->rows * _params->GetRegionHeight() * _params->GetVerticalCoverage());

          if (_params->GetSnapToEdges())
          {
            if (i == 0) tl.x = (int)(_input->GetDepthImage()->cols * (1 - _params->GetHorizontalCoverage()) / 2);
            if (i == _params->GetVerticalRegions() - 1) br.x = (int)(_input->GetDepthImage()->cols * (1 + _params->GetHorizontalCoverage()) / 2);
            if (j == 0) tl.y = (int)(_input->GetDepthImage()->rows * (1 - _params->GetVerticalCoverage()) / 2);
            if (j == _params->GetHorizontalRegions() - 1) br.y = (int)(_input->GetDepthImage()->rows * (1 + _params->GetVerticalCoverage()) / 2);
          }

          _output->SetRegionBounds(i, j, Rect(tl, br) & Rect(0, 0, _input->GetDepthImage()->cols, _input->GetDepthImage()->rows));
        }
    }

    void Base::FindMaxInRegions()
    {
      Mat hist;
      int size[] = { _params->GetHistogramBins() };
      float range[] = { _params->GetMinimumDistance(), _params->GetMaximumDistance() };
      const float* ranges[] = { range };
      int channels[] = { 0 };

      float sum = 0;
      float total = 0;

      for (int i = 0; i < _params->GetHorizontalRegions(); ++i)
        for (int j = 0; j < _params->GetVerticalRegions(); ++j)
        {
          calcHist(&(*_input->GetDepthImage())(_output->GetRegionBounds(j, i)), 1, channels, _maskImage(_output->GetRegionBounds(j, i)), hist, 1, size, ranges, true, false);
          normalize(hist, hist, 0, hist.rows, NORM_MINMAX, -1, Mat());

          sum = (float)cv::sum(hist)[0];
          total = 0;

          for (int k = 0; k < _params->GetHistogramBins(); ++k)
          {
            total += hist.at<float>(k);

            if (total > sum * _params->GetPercentileToIgnore())
            {
              _output->SetRegionIntensity(j, i, (int)(_params->GetMinimumDistance() + k * (_params->GetMaximumDistance() - _params->GetMinimumDistance()) / (float)_params->GetHistogramBins()));
              break;
            }
          }
        }
    }

    void Base::MapVibrationValues()
    {
      float slope = 0.f;
      for (int i = 0; i < VERT_REGIONS; ++i)
      {
        float intensity = 0.f;
        for (int j = 0; j < HORZ_REGIONS; ++j)
        {
          slope = (_params->GetMaximumVibration() - _params->GetMinimumVibration()) / (_params->GetFarthestBound(i, j) - _params->GetNearestBound()); // calculate the slope between nearest and farthest points.
          intensity = max(intensity, min(_params->GetMaximumVibration(), _params->GetMaximumVibration() - max(0.f, _output->GetRegionIntensity(i, j) - _params->GetNearestBound()) * slope)); // map the value to a vibration intensity ratio, and the maximum for that finger.
        }
        _output->GetVibrationIntensity()[i]->Update(intensity);
      }
    }
  }
}