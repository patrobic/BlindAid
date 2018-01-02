#pragma once

#include "IDetect.h"
#include "Capture.h"

#define DEPTH_RANGE 256

namespace Vision
{
  namespace DepthObstacle
  {
    class Data : public IData
    {
    public:
      void Clear() { for (int i = 0; i < VERT_REGIONS; ++i) for (int j = 0; j < HORZ_REGIONS; ++j) _regions[i][j].Clear(); _handPosition = cv::Point(0, 0); }

      bool Valid()
      {
        return true;
      }

      cv::Rect GetRegionBounds(int col, int row) { return _regions[col][row]._region; }
      void SetRegionBounds(int col, int row, cv::Rect region) { _regions[col][row]._region = region; }

      int GetRegionIntensity(int col, int row) { return _regions[col][row]._intensity; }
      void SetRegionIntensity(int col, int row, int intensity) { _regions[col][row]._intensity = intensity; }

      cv::Point GetHandPosition() { return _handPosition; }
      void SetHandPosition(cv::Point handPosition) { _handPosition = handPosition; }

      int GetMinColIntensity(int col) {
        int min = 255;
        for (int i = 0; i < HORZ_REGIONS; ++i)
          min = std::min(min, _regions[col][i]._intensity);
        return min;
      }

      int GetMinRowIntensity(int row) {
        int min = 255;
        for (int i = 0; i < HORZ_REGIONS; ++i)
          min = std::min(min, _regions[i][row]._intensity);
        return min;
      }

    private:
      cv::Point _handPosition;
      std::array<std::array<Region, HORZ_REGIONS>, VERT_REGIONS> _regions;
    };

    class Detect : public IDetect<Parameters, Capture::Data, Data>
    {
    public:
      Detect(IParameters *params, IData *input, IData *output);

    private:
      void Process();
      void MaskShadows();
      void SetCenterPoint();
      void DetectHand();
      void SeparateRegions();
      void FindMaxInRegions();

      cv::Mat _grayImage;
      cv::Mat _maskImage;
    };
  }
}