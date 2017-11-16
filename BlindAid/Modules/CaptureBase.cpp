#include "CaptureBase.h"
#include "CaptureRealtime.h"
#include "CaptureSimulate.h"

namespace Capture
{
  //template<class Params>
  //Base<Params>::Base(IParameters *params, IData *input, IData *output) : IModule(params, input, output)
  //{

  //}

//  template<class Params>
  IIModule *MakeCapture(Capture::Parameters *params, IData *input, IData *output)
  {
    if (((Capture::Parameters*)params)->GetMode() == SwitchableParameters::Mode::Realtime)
      return new Realtime::Realtime(params->GetRealtimeParams(), input, output);
    else
      return new Simulate::Simulate(params->GetSimulateParams(), input, output);
  }

  //template<class Params>
  //void Base<Params>::CreateHsvImage()
  //{
  //  cvtColor(*_output->GetRgbImage(), *_output->GetHsvImage(), CV_BGR2HSV);
  //}
}