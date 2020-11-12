#pragma once

#include "IParameters.h"
#include "DepthObstacleParameters.h"
#include "TrafficLightParameters.h"
#include "opencv2\core.hpp"

namespace Vision
{
  class Parameters : public SwitchableParameters
  {
  public:
    Parameters(GlobalParameters *params) : SwitchableParameters(params), _dodParams(params), _tldParams(params)
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

    DepthObstacle::Parameters *GetDepthObstacleParams() { return &_dodParams; }
    TrafficLight::Parameters *GetTrafficLightParams() { return &_tldParams; }

  private:
    // parameters class for depth obstacle detector.
    DepthObstacle::Parameters _dodParams;

    // parameters class for traffic light detector.
    TrafficLight::Parameters _tldParams;
  };
}