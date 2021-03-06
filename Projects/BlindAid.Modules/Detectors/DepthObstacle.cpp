#include "DepthObstacle.h"
#include "DepthObstacleFixedRegions.h"
#include "DepthObstacleHandPosition.h"

using namespace std;
using namespace cv;

namespace Vision
{
  namespace DepthObstacle
  {
    DepthObstacle *DepthObstacle::MakeDepthObstacle(IParameters *params, IData *input, IData *output, Tools::Logger *logger)
    {
      if (((DepthObstacleParameters*)params)->GetVersion() == DepthObstacleParameters::Version::FixedRegions)
        return new FixedRegions::FixedRegions(params, input, output, logger);
      else
        return new HandPosition::HandPosition(params, input, output, logger);
    }

    DepthObstacle::DepthObstacle(IParameters *params, IData *input, IData *output, Tools::Logger *logger) : IDetect(params, input, output, logger)
    {
      _output->SetHandPosition(_params->GetDefaultCenter());

      for (int i = 0; i < _params->GetFrameConsecutiveCount(); ++i)
        _lastImages.push_back(Mat(468, 628, CV_16UC1));
    }

    DepthObstacle::~DepthObstacle()
    {

    }
    
    void DepthObstacle::FindConsecutiveMax()
    {
      _index = ++_index%_params->GetFrameConsecutiveCount();

      _input->GetDepthImage()->copyTo(_lastImages[_index]);

      for (int i = 0; i < _params->GetFrameConsecutiveCount(); ++i)
        max(_lastImages[_index], *_input->GetDepthImage(), *_input->GetDepthImage());

      _input->GetDepthImage()->forEach<unsigned short>([&](unsigned short &pixel, const int * position) -> void {
        for (int i = 0; i < _params->GetFrameConsecutiveCount(); ++i)          
          if (_lastImages[i].at<unsigned short>(position) == 0)
            pixel = 0;
      });
    }
    
    void DepthObstacle::MaskShadows()
    {
      inRange(*_input->GetDepthImage(), _params->GetMinimumDistance(), _params->GetMaximumDistance(), _maskImage);
    }

    void DepthObstacle::SeparateRegions()
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

          _output->SetRegion(i, j, Rect(tl, br) & Rect(0, 0, _input->GetDepthImage()->cols, _input->GetDepthImage()->rows));
        }
    }

    void DepthObstacle::FindMaxInRegions()
    {
      Mat hist;
      int size[] = { _params->GetHistogramBins() };
      float range[] = { _params->GetMinimumDistance(), _params->GetMaximumDistance() };
      const float* ranges[] = { range };
      int channels[] = { 0 };

      float total = 0;
      for (int i = 0; i < _params->GetHorizontalRegions(); ++i)
        for (int j = 0; j < _params->GetVerticalRegions(); ++j)
        {
          calcHist(&(*_input->GetDepthImage())(_output->GetRegion(j, i)), 1, channels, _maskImage(_output->GetRegion(j, i)), hist, 1, size, ranges, true, false);

          if (countNonZero(_maskImage(_output->GetRegion(j, i))) / (float)(*_input->GetDepthImage())(_output->GetRegion(j, i)).total() < _params->GetValidRatioThreshold())
            _output->SetDepth(j, i, (int)_params->GetMaximumDistance());
          else
          {
            total = 0;
            for (int k = 0; k < _params->GetHistogramBins(); ++k)
            {
              total += hist.at<float>(k);

              if (total > (*_input->GetDepthImage())(_output->GetRegion(j, i)).total() * _params->GetPercentileToIgnore())
              {
                _output->SetDepth(j, i, (int)(_params->GetMinimumDistance() + k * (_params->GetMaximumDistance() - _params->GetMinimumDistance()) / (float)_params->GetHistogramBins()));
                break;
              }
            }
          }
        }
    }

    void DepthObstacle::MapVibrationValues()
    {
      float slope = 0.f;
      for (int i = 0; i < VERT_REGIONS; ++i)
      {
        float intensity = 0.f;
        for (int j = 0; j < HORZ_REGIONS; ++j)
        {
          slope = (_params->GetMaximumVibration() - _params->GetMinimumVibration()) / (_params->GetMinimumDistance() - _params->GetFarthestBound(i, j)); // calculate the slope between nearest and farthest points.
          intensity = max(intensity, (_output->GetDepth(i, j) > _params->GetFarthestBound(i, j)) ? 0.f : max(0.f, _output->GetDepth(i, j) - _params->GetMinimumDistance()) * slope + _params->GetMaximumVibration()); // map the value to a vibration intensity ratio, and the maximum for that finger.
        }
        _output->SetVibration(i, intensity);
      }
    }
  }
}