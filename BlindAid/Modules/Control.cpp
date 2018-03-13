#include "Control.h"
#include "ControlRealtime.h"
#include "ControlSimulate.h"

using namespace std;
using namespace cv;

namespace Control
{
  Base *Base::MakeControl(IParameters *params, IData *input, IData *output, Logger *logger)
  {
    if (((Control::Parameters*)params)->GetMode() == Mode::Realtime)
      return new Realtime::Realtime(params, input, output, logger);
    else
      return new Simulate::Simulate(params, input, output, logger);
  }

  Base::Base(IParameters *params, IData *input, IData *output, Logger *logger) : IModule(params, input, output, logger)
  {

  }
}