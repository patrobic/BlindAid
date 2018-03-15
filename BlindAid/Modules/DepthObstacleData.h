#pragma once

#include "DepthObstacleResult.h"

#include "opencv2\core.hpp"

namespace Vision
{
  namespace DepthObstacle
  {
    class Data : public IData
    {
    public:
      Data(Parameters *params)
      {
        for (int i = 0; i < 5; ++i)
          _vibration.push_back(Result(params->GetConsecutiveCount()));
      }

      void Clear()
      {

      }

      bool Valid()
      {
        return true;
      }

      std::string _names[7] = { "Thumb", "Index", "Middle", "Ring", "Pinky", "Option1", "Option2" };

      cv::Rect GetRegion(int col, int row)
      {
        return _regions[col][row];
      }

      int GetDepth(int col, int row)
      {
        return _depth[col][row];
      }

      cv::Point GetHandPosition()
      {
        return _handPosition;
      }

      float GetMaxVibration()
      {
        float max = 0.f;

        for (int i = 0; i < VERT_REGIONS; ++i)
          max = std::max(max, _vibration[i].Get());

        return max;
      }

      Result *GetVibration(int index)
      {
        return &_vibration.at(index);
      }

      void SetRegion(int col, int row, cv::Rect region)
      {
        _regions[col][row] = region;
      }

      void SetDepth(int col, int row, int depth)
      {
        _depth[col][row] = depth;
      }

      void SetHandPosition(cv::Point handPosition)
      {
        _handPosition = handPosition;
      }

    private:
      cv::Rect _regions[VERT_REGIONS][HORZ_REGIONS];
      int _depth[VERT_REGIONS][HORZ_REGIONS];
      cv::Point _handPosition = cv::Point(0, 0);
      std::vector<Result> _vibration;
    };
  }
}