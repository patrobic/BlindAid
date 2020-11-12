#pragma once

#include "DisplayParameters.h"
#include "IModule.h"
#include "Vision.h"
#include "DisplayData.h"

namespace Display
{
  class Display : public IModule<DisplayParameters, Vision::VisionData, Capture::CaptureData>
  {
  public:
    Display(IParameters *params, IData *input, IData *output, Logger *logger);

  private:
    void Process();
    void DrawDepthObstacles();
    void DrawTrafficLights();
    void DrawTrafficLightBD();
    void DrawTrafficLightDL();
    void DisplayColorImage();
    void DisplayDepthImage();
  };
}