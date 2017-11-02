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

  class Data : public IData
  {
  public:
    void Clear() {}

  private:

  };

  ControlBase(IParameters *params, IData *input, IData *output)
  {
    _params = static_cast<Parameters*>(params);
    _input = static_cast<Vision::Data*>(input);
    _output = static_cast<Data*>(output);
  }
  virtual void operator()() = 0;

protected:
  Parameters *_params;
  Vision::Data *_input;
  Data *_output;
};

class Control : public ControlBase
{
public:
  Control(IParameters *params, IData *input, IData *output) : ControlBase(params, input, output) {}
  void operator()();

  // TODO: Implement class to control the Glove's Arduino(?) hardware once we have a working prototype.
private:
};