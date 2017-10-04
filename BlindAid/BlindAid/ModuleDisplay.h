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

  void Init(Data *data, IParameters *params, IResults *input, IResults *output);
  void operator()();

private:
  void DisplayThread();

  void ShowDepthObstacles();
  void ShowTrafficLights();
  void ShowStopSign();

  void DisplayImage();

  Data *_data;
  Parameters *_params;
  Vision::Results *_input;
  Results *_output;
};