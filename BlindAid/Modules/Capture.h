#pragma once

#include "IModule.h"
#include "CaptureParameters.h"
#include "CaptureData.h"

namespace Capture
{
  class Base : public IModule<Parameters, IData, Data>
  {
  public:
    Base(IParameters *params, IData *input, IData *output, Logger *logger);
    virtual ~Base();
    static Base *MakeCapture(Capture::Parameters *params, IData *input, IData *output, Logger *logger);

  protected:
  };
}
