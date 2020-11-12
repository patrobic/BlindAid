#pragma once

#include "IModule.h"
#include "CaptureParameters.h"
#include "CaptureData.h"

namespace Capture
{
  class Capture : public IModule<CaptureParameters, IData, CaptureData>
  {
  public:
    Capture(IParameters *params, IData *input, IData *output, Logger *logger);
    virtual ~Capture();
    static Capture *MakeCapture(IParameters *params, IData *input, IData *output, Logger *logger);

  protected:
  };
}
