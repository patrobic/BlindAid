#pragma once

#include "IModule.h"
#include "Vision.h"
#include "ControlParameters.h"
#include "ControlData.h"

namespace Control
{
  class Base : public IModule<Parameters, Vision::Data, Data>
  {
  public:
    Base(IParameters *params, IData *input, IData *output, Logger *logger);
    virtual ~Base();
    static Base * MakeControl(IParameters * params, IData * input, IData * output, Logger *logger);

  protected:
  };
}