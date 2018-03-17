#include "Capture.h"
#include "CaptureRealtime.h"
#include "CaptureSimulate.h"

namespace Capture
{
  Base::Base(IParameters *params, IData *input, IData *output, Logger *logger) : IModule(params, input, output, logger)
  {

  }

  Base::~Base()
  {

  }

  Base *Base::MakeCapture(Capture::Parameters *params, IData *input, IData *output, Logger *logger)
  {
    if (((Capture::Parameters*)params)->GetMode() == Mode::Realtime)
      return new Realtime::Realtime(params, input, output, logger);
    else
      return new Simulate::Simulate(params, input, output, logger);
  }
}