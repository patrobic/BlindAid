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

protected:
  Data *_data;
  Parameters *_params;
  Vision::Results *_input;
  Results *_output;
};

class Control : public ControlBase
{
  void Init(Data *data, IParameters *params, IResults *input, IResults *output);
  void operator()();

  // TODO: Implement class to control the Glove's Arduino(?) hardware once we have a working prototype.
private:
};