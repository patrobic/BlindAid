#pragma once

#include "IParameters.h"
#include "DepthObstacleParameters.h"
#include "TrafficLightParameters.h"
#include "opencv2\core.hpp"

namespace Vision
{
  class VisionParameters : public SwitchableParameters
  {
  public:
    VisionParameters(GlobalParameters *params) : SwitchableParameters(params), _dodParams(params), _tldParams(params)
    {
      Defaults();
    }

    void Defaults()
    {
      _dodParams.Defaults();
      _tldParams.Defaults();
    }

    bool Valid()
    {
      return true;
    }

    DepthObstacle::DepthObstacleParameters *GetDepthObstacleParams() { return &_dodParams; }
    TrafficLight::TrafficLightParameters *GetTrafficLightParams() { return &_tldParams; }

  private:
    // parameters class for depth obstacle detector.
    DepthObstacle::DepthObstacleParameters _dodParams;

    // parameters class for traffic light detector.
    TrafficLight::TrafficLightParameters _tldParams;
  };
}