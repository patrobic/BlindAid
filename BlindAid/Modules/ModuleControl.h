#pragma once

#include "IModule.h"
#include "ModuleVision.h"

class ControlBase : public IModule
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

  ControlBase(Data *data, IParameters *params, IResults *input, IResults *output)
  {
    _data = data;
    _params = static_cast<Parameters*>(params);
    _input = static_cast<Vision::Results*>(input);
    _output = static_cast<Results*>(output);
  }
  virtual void operator()() = 0;


protected:
  Data *_data;
  Parameters *_params;
  Vision::Results *_input;
  Results *_output;
};

class Control : public ControlBase
{
public:
  Control(Data *data, IParameters *params, IResults *input, IResults *output) : ControlBase(data, params, input, output) {}
  void operator()();

  // TODO: Implement class to control the Glove's Arduino(?) hardware once we have a working prototype.
private:
};