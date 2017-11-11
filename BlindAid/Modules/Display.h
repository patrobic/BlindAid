#pragma once

#include "IModule.h"
#include "Vision.h"

namespace Display
{
  class Parameters : public IParameters
  {
  public:
    bool Valid()
    {
      return true;
    }

  private:

  };

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

  class Display : public IModule<Parameters, Vision::Data, Data>
  {
  public:
    Display(IParameters *params, IData *input, IData *output);

  private:
    void Process();
    void DrawDepthObstacles();
    void DrawTrafficLights();
    void DrawStopSign();
    void DisplayImage();
  };
}