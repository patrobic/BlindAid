#pragma once

#include "IModule.h"
#include "CaptureSimulate.h"

#include "DepthObstacle.h"
#include "TrafficLightBase.h"
#include "StopSign.h"

namespace Vision
{
  class Parameters : public IParameters
  {
  public:
    DepthObstacle::Parameters *GetDepthObstacleParams() { return &_dodParams; }
    TrafficLight::Parameters *GetTrafficLightParams() { return &_tldParams; }
    StopSign::Parameters *GetStopSignParams() { return &_ssdParams; }

    bool Valid()
    {
      return true;
    }

  private:
    // parameters class for depth obstacle detector.
    DepthObstacle::Parameters _dodParams;

    // parameters class for traffic light detector.
    TrafficLight::Parameters _tldParams;

    // parameters class for stop sign detector.
    StopSign::Parameters _ssdParams;
  };

  class Data : public IData
  {
  public:
    void Clear() {}
    bool Valid()
    {
      return true;
    }

    DepthObstacle::Data *GetDepthObstacleResults() { return &_dodResults; }
    TrafficLight::Data *GetTrafficLightResults() { return &_tldResults; }
    StopSign::Data *GetStopSignResults() { return &_ssdResults; }

    cv::Mat *GetCurrentColorImage() { return _currentColorImage; }
    cv::Mat *GetCurrentDepthImage() { return _currentDepthImage; }

    void SetCurrentColorImage(cv::Mat *mat) { _currentColorImage = mat; }
    void SetCurrentDepthImage(cv::Mat *mat) { _currentDepthImage = mat; }

  private:
    DepthObstacle::Data _dodResults;
    TrafficLight::Data _tldResults;
    StopSign::Data _ssdResults;

    cv::Mat *_currentColorImage;
    cv::Mat *_currentDepthImage;
  };

  class Vision : public IModule<Parameters, Capture::Data, Data>
  {
  public:
    Vision(IParameters *params, IData *input, IData *output);

  private:
    void Process();
    
    DepthObstacle::Detect *_depthObstacle;
    TrafficLight::Base *_trafficLight;
    StopSign::Detect *_stopSign;
  };
}