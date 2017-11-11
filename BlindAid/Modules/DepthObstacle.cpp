#include "DepthObstacle.h"

using namespace std;
using namespace cv;

namespace Vision
{
  namespace DepthObstacle
  {
    Detect::Detect(IParameters *params, IData *input, IData *output) : DetectBase(params, input, output)
    {

    }

    void Detect::Process()
    {
      MaskShadows();
      SetCenterPoint();
      SeparateRegions();
      FindMaxInRegions();
    }

    void Detect::MaskShadows()
    {
      cvtColor(*_input->GetDepthImage(), _grayImage, CV_BGR2GRAY);
      threshold(_grayImage, _maskImage, 0, DEPTH_RANGE - 1, THRESH_BINARY);
    }

    void Detect::SetCenterPoint()
    {
      switch (_params->GetMode())
      {
      case(Parameters::Mode::HandHunting):
        DetectHand();
        break;
      case(Parameters::Mode::FingerRegions):
        _output->SetHandPosition(_params->GetDefaultHandPosition());
        break;
      case(Parameters::Mode::HeadProtection):
        _output->SetHandPosition(Point(_grayImage.cols / 2, _grayImage.rows * 1 / 3));
        break;
      }
    }

    void Detect::DetectHand()
    {
      // TODO: detect position of hand
      // use blobfinder hardcoded to expected color and size range of dot on glove, and limit to lower third of frame.

      Mat handDotMask;
      inRange(*_input->GetHsvImage(), _params->GetHandDotHsvRange(0), _params->GetHandDotHsvRange(1), handDotMask);

      Ptr<SimpleBlobDetector> sbd = SimpleBlobDetector::create(_params->GetSbdParams());

      vector<KeyPoint> keyPoints;
      sbd->detect(_grayImage, keyPoints);

      if (keyPoints.size() == 0)
        _output->SetHandPosition(Point(_grayImage.cols / 2, _grayImage.rows / 2));
      else
        _output->SetHandPosition(keyPoints.at(0).pt);
    }

    void Detect::SeparateRegions()
    {
      Point tl;
      Point br;

      for (int i = 0; i < VERT_REGIONS; ++i)
        for (int j = 0; j < HORZ_REGIONS; ++j)
        {
          if (_params->GetMode() == Parameters::Mode::HeadProtection && i != 2)
            continue;

          tl.x = _output->GetHandPosition().x + (int)((i - 2.5) * _grayImage.cols * _params->GetCenterRegionsWidth());
          br.x = _output->GetHandPosition().x + (int)((i - 1.5) * _grayImage.cols * _params->GetCenterRegionsWidth());
          tl.y = _output->GetHandPosition().y + (int)((j - 1.5) * _grayImage.rows * _params->GetCenterRegionHeight());
          br.y = _output->GetHandPosition().y + (int)((j - 0.5) * _grayImage.rows * _params->GetCenterRegionHeight());

          if (i == 0) tl.x = 0;
          if (i == VERT_REGIONS - 1) br.x = _grayImage.cols;
          if (j == 0) tl.y = 0;
          if (j == HORZ_REGIONS - 1) br.y = _grayImage.rows;

          _output->SetRegionBounds(i, j, Rect(tl, br) & Rect(0, 0, _grayImage.cols, _grayImage.rows));
        }
    }

    void Detect::FindMaxInRegions()
    {
      Mat hist;
      int size[] = { DEPTH_RANGE };
      float range[] = { 0, DEPTH_RANGE };
      const float* ranges[] = { range };
      int channels[] = { 0 };

      float sum = 0;
      float total = 0;

      for (int i = 0; i < HORZ_REGIONS; ++i)
        for (int j = 0; j < VERT_REGIONS; ++j)
        {
          calcHist(&_grayImage(_output->GetRegionBounds(j, i)), 1, channels, _maskImage(_output->GetRegionBounds(j, i)), hist, 1, size, ranges, true, false);
          normalize(hist, hist, 0, hist.rows, NORM_MINMAX, -1, Mat());

          sum = (float)cv::sum(hist)[0];
          total = 0;

          for (int k = 0; k < DEPTH_RANGE; ++k)
          {
            total += hist.at<float>(k);

            if (total > sum * _params->GetPercentileToIgnore())
            {
              _output->SetRegionIntensity(j, i, k);
              break;
            }
          }
        }
    }
  }
}