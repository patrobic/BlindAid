#include "SimulateControl.h"

using namespace std;
using namespace cv;

void ControlSim::Init(Data *data)
{
  _data = data;
}

void ControlSim::operator()()
{
  _data->_controlThread = thread(&ControlSim::ControlThread, this);
}

void ControlSim::SimulateOutput(int frame)
{
  cout << "[CONTROL] Frame " << to_string(frame) << " received.\n";
  cout << "[GLOVE] \
Thumb(" << _data->_results.GetDepthObstacleResults().GetMinColIntensity(0) << "), \
Index(" << _data->_results.GetDepthObstacleResults().GetMinColIntensity(1) << "), \
Middle(" << _data->_results.GetDepthObstacleResults().GetMinColIntensity(2) << "), \
Ring(" << _data->_results.GetDepthObstacleResults().GetMinColIntensity(3) << "), \
Pinky(" << _data->_results.GetDepthObstacleResults().GetMinColIntensity(4) << "), \
Upper(" << _data->_results.GetDepthObstacleResults().GetMinColIntensity(0) << "), \
Lower(" << _data->_results.GetDepthObstacleResults().GetMinRowIntensity(2) << ").\n";

  int trafficLightCount = _data->_results.GetTrafficLightResults().Size();
  int stopSignCount = _data->_results.GetStopSignResults().GetRegion()._radius > 0 ? 1 : 0;
  
  cout << "[AUDIO]";
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
