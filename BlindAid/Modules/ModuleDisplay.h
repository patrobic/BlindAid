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

  class Results : public IResults
  {
  public:
    void Clear() {}

  private:

  };

  Display(Data *data, IParameters *params, IResults *input, IResults *output);
  void operator()();

private:
  void DrawDepthObstacles();
  void DrawTrafficLights();
  void DrawStopSign();

  void DisplayImage();

  Parameters *_params;
  Vision::Results *_input;
  Results *_output;
};