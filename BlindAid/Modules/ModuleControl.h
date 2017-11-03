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
  float CalculateVibrationValue(int pixel)
  {
    float control = 0.f;

    // TODO: design algorithm that calculates vibrator control value (voltage/factor/whatever is required by the API controlling the Arduino/glove).
    // Should implement a function that maps the nearest pixel intensity value to control value in some non-linear way,
    // giving higher weight to near objects (possibly negative exponential function?).
    // [intensity]
    // |.......
    // |       .....
    // |            ...
    // |               ..
    // |                 .
    // |__________________._____________ [distance]
    // 0             128             255

    return control;
  }

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