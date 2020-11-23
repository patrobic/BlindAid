#pragma once

#include "IModule.h"
#include "CaptureSimulate.h"
#include "VisionData.h"

namespace Vision
{
  class Vision : public IModule<VisionParameters, Capture::CaptureData, VisionData>
  {
  public:
    Vision(IParameters *params, IData *input, IData *output, Tools::Logger *logger);
    ~Vision();

  private:
    void Process();
    void RunModules();
    
    DepthObstacle::DepthObstacle *_depthObstacle;
    TrafficLight::TrafficLight *_trafficLight;
  };
}