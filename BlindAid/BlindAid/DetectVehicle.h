#pragma once

#include "IModule.h"
#include "ModuleVision.h"

class DetectVehicle : public IModule
{
public:
  struct Parameters : public IParameters
  {
  public:

  private:
  };

  class Results : public IResults
  {
  public:

  private:

  };

  void Init(Data *data, IParameters *params, IResults *input, IResults *output);
  void operator()();

private:
  Parameters *_params;
  Vision::Results *_input;
  Results *_output;
};