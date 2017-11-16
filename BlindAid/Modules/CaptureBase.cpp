#include "CaptureBase.h"
#include "CaptureRealtime.h"
#include "CaptureSimulate.h"

namespace Capture
{
  Base::Base(IParameters *params, IData *input, IData *output) : IModule(params, input, output)
  {

  }

  Base *Base::MakeCapture(Capture::Parameters *params, IData *input, IData *output)
  {
    if (((Capture::Parameters*)params)->GetMode() == SwitchableParameters::Mode::Realtime)
      return new Realtime::Realtime(params, input, output);
    else
      return new Simulate::Simulate(params, input, output);
  }

  void Base::CreateHsvImage()
  {
    cvtColor(*_output->GetRgbImage(), *_output->GetHsvImage(), CV_BGR2HSV);
  }
}