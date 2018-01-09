#pragma once

#include "opencv2\core.hpp"

namespace Vision
{
  namespace DepthObstacle
  {
    class Result
    {
    public:
      Result(int size)
      {
        _vibration.resize(size);
      }

      void Update(float intensity)
      {
        _vibration[index++%_vibration.size()] = intensity;
      }

      float GetFiltered()
      {
        float intensity = (float)INT_MAX;

        for (int i = 0; i < _vibration.size(); ++i)
          intensity = std::min(intensity, _vibration[i]);

        return intensity;
      }

    private:
      int index = 0;

      std::vector<float> _vibration;
    };

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

      Result **GetVibrationIntensity() { return _vibrationIntensity; }

    private:
      cv::Point _handPosition;
      std::array<std::array<Region, HORZ_REGIONS>, VERT_REGIONS> _regions;
      Result *_vibrationIntensity[VERT_REGIONS + 2];
    };
  }
}