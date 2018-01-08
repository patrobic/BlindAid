#include "Control.h"
#include "ControlRealtime.h"
#include "ControlSimulate.h"

using namespace std;
using namespace cv;

namespace Control
{
  Base *Base::MakeControl(IParameters *params, IData *input, IData *output)
  {
    if (((Control::Parameters*)params)->GetMode() == SwitchableParameters::Mode::Realtime)
      return new Realtime::Realtime(params, input, output);
    else
      return new Simulate::Simulate(params, input, output);
  }

  Base::Base(IParameters *params, IData *input, IData *output) : IModule(params, input, output)
  {
    for (int i = 0; i < VERT_REGIONS + 2; ++i) _input->GetDepthObstacleResults()->GetVibrationIntensity()[i] = new Vision::DepthObstacle::Result(_params->GetConsecutiveCount());
  }
}