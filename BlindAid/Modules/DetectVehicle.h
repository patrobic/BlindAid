#pragma once

#include "IModule.h"
#include "ModuleCapture.h"

class DetectVehicle : public DetectBase
{
public:
  struct Parameters : public IParameters
  {
  public:

  private:
  };

  class Data : public IData
  {
  public:

  private:

  };

  DetectVehicle(IParameters *params, IData *input, IData *output)
  {
    _params = static_cast<Parameters*>(params);
    _input = static_cast<Capture::Data*>(input);
    _output = static_cast<Data*>(output);
  }
  void operator()();

private:
  Parameters *_params;
  Capture::Data *_input;
  Data *_output;
};