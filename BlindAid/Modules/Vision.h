#pragma once

#include "IModule.h"
#include "CaptureSimulate.h"
#include "VisionData.h"

namespace Vision
{
  class Vision : public IModule<Parameters, Capture::Data, Data>
  {
  public:
    Vision(IParameters *params, IData *input, IData *output, Logger *logger);

  private:
    void CreateModules();
    void Process();
    void RunModules();
    
    DepthObstacle::Base *_depthObstacle;
    TrafficLight::Base *_trafficLight;
    StopSign::Base *_stopSign;
  };
}