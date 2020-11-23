#pragma once

#include "IResult.h"

#include "opencv2\core.hpp"

namespace Vision
{
  namespace DepthObstacle
  {
    class DepthObstacleResult : public IResult
    {
    public:
      DepthObstacleResult(int size)
      {
        _vibration.resize(size);
      }

      void Clear()
      {

      }

      void Set(float intensity)
      {
        _vibration[_index++%_vibration.size()] = intensity;
      }

      float Get()
      {
        if (_vibration.size() == 1)
          return _vibration[0];

        float intensity = (float)INT_MAX;

        for (int i = 0; i < _vibration.size(); ++i)
          intensity = std::min(intensity, _vibration[i]);

        return intensity;
      }

    private:
      int _index = 0;
      std::vector<float> _vibration;
    };
  }
}