#pragma once

#include "IModule.h"
#include "SimulateCapture.h"

#include "DetectDepthObstacle.h"
#include "DetectTrafficLight.h"
#include "DetectStopSign.h"

class Vision : public IModule
{
public:
  class Parameters : public IParameters
  {
  public:
    DetectDepthObstacle::Parameters *GetDepthObstacleParams() { return &_dodParams; }
    DetectTrafficLight::Parameters *GetTrafficLightParams() { return &_tldParams; }
    DetectStopSign::Parameters *GetStopSignParams() { return &_ssdParams; }

  private:
    // parameters class for depth obstacle detector.
    DetectDepthObstacle::Parameters _dodParams;

    // parameters class for traffic light detector.
    DetectTrafficLight::Parameters _tldParams;

    // parameters class for stop sign detector.
    DetectStopSign::Parameters _ssdParams;
  };

  class Data : public IData
  {
  public:
    void Clear() {}

    DetectTrafficLight::Data *GetTrafficLightResults() { return &_tldResults; }
    DetectStopSign::Data *GetStopSignResults() { return &_ssdResults; }
    DetectDepthObstacle::Data *GetDepthObstacleResults() { return &_dodResults; }

    cv::Mat *GetCurrentColorImage() { return _currentColorImage; }
    cv::Mat *GetCurrentDepthImage() { return _currentDepthImage; }

    void SetCurrentColorImage(cv::Mat *mat) { _currentColorImage = mat; }
    void SetCurrentDepthImage(cv::Mat *mat) { _currentDepthImage = mat; }

  private:
    DetectTrafficLight::Data _tldResults;
    DetectStopSign::Data _ssdResults;
    DetectDepthObstacle::Data _dodResults;

    cv::Mat *_currentColorImage;
    cv::Mat *_currentDepthImage;
  };

  Vision(IParameters *params, IData *input, IData *output);
  void operator()();

private:
  Parameters *_params;
  CaptureSim::Data *_input;
  Data *_output;

  DetectStopSign _stopSign;
  DetectTrafficLight _trafficLight;
  DetectDepthObstacle _depthObstacle;
};