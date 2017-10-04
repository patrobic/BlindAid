#include "SimulateControl.h"

using namespace std;
using namespace cv;

void ControlSim::Init(Data *data, IParameters *params, IResults *input, IResults *output)
{
  _data = data;
  _params = static_cast<Parameters*>(params);
  _input = static_cast<Vision::Results*>(input);
  _output = static_cast<Results*>(output);
}

void ControlSim::operator()()
{
  _data->_controlThread = thread(&ControlSim::ControlThread, this);
}

void ControlSim::SimulateOutput(int frame)
{
  cout << "[CONTROL] Frame " << to_string(frame) << " received.\n";
  cout << "\t[GLOVE] \
Thumb(" << _input->GetDepthObstacleResults()->GetMinColIntensity(0) << "), \
Index(" << _input->GetDepthObstacleResults()->GetMinColIntensity(1) << "), \
Middle(" << _input->GetDepthObstacleResults()->GetMinColIntensity(2) << "), \
Ring(" << _input->GetDepthObstacleResults()->GetMinColIntensity(3) << "), \
Pinky(" << _input->GetDepthObstacleResults()->GetMinColIntensity(4) << "), \
Upper(" << _input->GetDepthObstacleResults()->GetMinColIntensity(0) << "), \
Lower(" << _input->GetDepthObstacleResults()->GetMinRowIntensity(2) << ").\n";

  int trafficLightCount = _input->GetTrafficLightResults()->Size();
  int stopSignCount = _input->GetStopSignResults()->GetRegion()._radius > 0 ? 1 : 0;
  
  cout << "\t[AUDIO]";
  if (trafficLightCount > 0) cout << " TrafficLights(" << trafficLightCount << ")";
  if (stopSignCount > 0) cout << " StopSign(" << trafficLightCount << ")"; cout << ".\n";
}

void ControlSim::ControlThread()
{
  int frame = 0;

  do
  {
    if (_data->_newFrameForControl)
    {
      if (_data->_resultMutex.try_lock())
      {
        frame++;

        // TODO: implement VisionResults deep copy instead.
        _data->_resultMutex.unlock();
        _data->_newFrameForControl = false;

        SimulateOutput(frame);
      }
    }
    this_thread::sleep_for(chrono::milliseconds(33));
  }
  while (!_data->_visionDone || _data->_newFrameForControl);
}
