#pragma once

#include "DepthObstacle.h"
#include "TrafficLight.h"

namespace Vision
{
  class Data : public IData
  {
  public:
    Data(Parameters *params)
    {
      _dodResults = new DepthObstacle::Data(params->GetDepthObstacleParams());
      _tldResults = new TrafficLight::Data(params->GetTrafficLightParams());
    }

    void Clear() {}
    bool Valid()
    {
      return true;
    }

    DepthObstacle::Data *GetDepthObstacleResults() { return _dodResults; }
    TrafficLight::Data *GetTrafficLightResults() { return _tldResults; }

    cv::Mat *GetDepthOverlayImage() { return &_depthOverlayImage; }
    cv::Mat *GetColorOverlayImage() { return &_colorOverlayImage; }

  private:
    DepthObstacle::Data *_dodResults;
    TrafficLight::Data *_tldResults;

    cv::Mat _colorOverlayImage;
    cv::Mat _depthOverlayImage;
  };
}