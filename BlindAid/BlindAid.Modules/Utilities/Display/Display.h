#pragma once

#include "DisplayParams.h"
#include "IModule.h"
#include "Vision.h"

namespace Display
{
  class Data : public IData
  {
  public:
    void Clear() {}
    bool Valid()
    {
      return true;
    }

  private:

  };

  class Display : public IModule<Parameters, Vision::Data, Capture::Data>
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