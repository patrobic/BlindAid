#include "Control.h"
#include "ControlRealtime.h"
#include "ControlSimulate.h"

using namespace std;
using namespace cv;

namespace Control
{
  Control::Control(IParameters *params, IData *input, IData *output, Tools::Logger *logger) : IModule(params, input, output, logger)
  {

  }

  Control::~Control()
  {

  }

  Control *Control::MakeControl(IParameters *params, IData *input, IData *output, Tools::Logger *logger)
  {
    if (((ControlParameters*)params)->GetMode() == Mode::Realtime)
      return new Realtime::ControlRealtime(params, input, output, logger);
    else
      return new Simulate::ControlSimulate(params, input, output, logger);
  }
}