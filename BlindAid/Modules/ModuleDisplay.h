#pragma once

#include "IModule.h"
#include "ModuleVision.h"

class Display : public IModule
{
public:
  class Parameters : public IParameters
  {
  public:

  private:

  };

  class Data : public IData
  {
  public:
    void Clear() {}

  private:

  };

  Display(IParameters *params, IData *input, IData *output);
  void operator()();

private:
  void DrawDepthObstacles();
  void DrawTrafficLights();
  void DrawStopSign();

  void DisplayImage();

  Parameters *_params;
  Vision::Data *_input;
  Data *_output;
};