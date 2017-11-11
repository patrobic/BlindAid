#include "CaptureBase.h"
#include "CaptureRealtime.h"
#include "CaptureSimulate.h"

namespace Capture
{
  Base::Base(IParameters *params, IData *input, IData *output) : IModule(params, input, output)
  {

  }

  Base *Base::MakeCapture(IParameters *params, IData *input, IData *output)
  {
    if (params->GetMode() == IParameters::Mode::Realtime)
      return new Realtime(params, input, output);
    else
      return new Simulate(params, input, output);
  }

  void Base::CreateHsvImage()
  {
    cvtColor(*_output->GetRgbImage(), *_output->GetHsvImage(), CV_BGR2HSV);
  }
}