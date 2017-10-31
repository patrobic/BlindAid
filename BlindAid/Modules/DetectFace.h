#pragma once

#include "IModule.h"
#include "ModuleCapture.h"

class DetectFace : public DetectBase
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

  DetectFace(Data *data, IParameters *params, IResults *input, IResults *output)
  {
    _data = data;
    _params = static_cast<Parameters*>(params);
    _input = static_cast<Capture::Results*>(input);
    _output = static_cast<Results*>(output);
  }
  void operator()();

private:
  Parameters *_params;
  Capture::Results *_input;
  Results *_output;
};