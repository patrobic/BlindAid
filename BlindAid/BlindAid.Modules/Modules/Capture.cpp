#include "Capture.h"
#include "CaptureRealtime.h"
#include "CaptureSimulate.h"

namespace Capture
{
  Capture::Capture(IParameters *params, IData *input, IData *output, Logger *logger) : IModule(params, input, output, logger)
  {

  }

  Capture::~Capture()
  {

  }

  Capture *Capture::MakeCapture(IParameters *params, IData *input, IData *output, Logger *logger)
  {
    if (((CaptureParameters*)params)->GetMode() == Mode::Realtime)
      return new Realtime::CaptureRealtime(params, input, output, logger);
    else
      return new Simulate::CaptureSimulate(params, input, output, logger);
  }
}