#pragma once

#include "DepthObstacle.h"
#include "TrafficLight.h"

namespace Vision
{
  class VisionData : public IData
  {
  public:
    VisionData(VisionParameters *params)
    {
      _dodResults = new DepthObstacle::DepthObstacleData(params->GetDepthObstacleParams());
      _tldResults = new TrafficLight::TrafficLightData(params->GetTrafficLightParams());
    }

    ~VisionData()
    {
      delete _dodResults;
      delete _tldResults;
    }

    void Clear() {}
    bool Valid()
    {
      return true;
    }

    DepthObstacle::DepthObstacleData *GetDepthObstacleResults() { return _dodResults; }
    TrafficLight::TrafficLightData *GetTrafficLightResults() { return _tldResults; }

    cv::Mat *GetDepthOverlayImage() { return &_depthOverlayImage; }
    cv::Mat *GetColorOverlayImage() { return &_colorOverlayImage; }

  private:
    DepthObstacle::DepthObstacleData *_dodResults;
    TrafficLight::TrafficLightData *_tldResults;

    cv::Mat _colorOverlayImage;
    cv::Mat _depthOverlayImage;
  };
}