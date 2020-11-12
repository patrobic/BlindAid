#pragma once

#include "IModule.h"
#include "Vision.h"
#include "ControlParameters.h"
#include "ControlData.h"

namespace Control
{
  class Control : public IModule<ControlParameters, Vision::VisionData, ControlData>
  {
  public:
    Control(IParameters *params, IData *input, IData *output, Tools::Logger *logger);
    virtual ~Control();
    static Control * MakeControl(IParameters * params, IData * input, IData * output, Tools::Logger *logger);

  protected:
  };
}