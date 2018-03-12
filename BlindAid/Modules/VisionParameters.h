#pragma once

#include "IParameters.h"
#include "DepthObstacleParameters.h"
#include "TrafficLightParameters.h"
#include "opencv2\core.hpp"

namespace Vision
{
  namespace StopSign
  {
    struct Parameters : public SwitchableParameters
    {
    public:
      Parameters(GlobalParameters *params) : SwitchableParameters(params)
      { 
        Defaults();
      }

      void Defaults()
      {

      }

      bool Valid()
      {
        return true;
      }

    private:

    };
  }

  class Parameters : public SwitchableParameters
  {
  public:
    Parameters(GlobalParameters *params) : SwitchableParameters(params), _dodParams(params), _tldParams(params), _ssdParams(params)
    {
      Defaults();
    }

    void Defaults()
    {
      _dodParams.Defaults();
      _tldParams.Defaults();
      _ssdParams.Defaults();
    }

    bool Valid()
    {
      return true;
    }

    DepthObstacle::Parameters *GetDepthObstacleParams() { return &_dodParams; }
    TrafficLight::Parameters *GetTrafficLightParams() { return &_tldParams; }
    StopSign::Parameters *GetStopSignParams() { return &_ssdParams; }

  private:
    // parameters class for depth obstacle detector.
    DepthObstacle::Parameters _dodParams;

    // parameters class for traffic light detector.
    TrafficLight::Parameters _tldParams;

    // parameters class for stop sign detector.
    StopSign::Parameters _ssdParams;
  };
}