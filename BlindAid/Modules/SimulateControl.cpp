#include "SimulateControl.h"

using namespace std;
using namespace std::chrono;
using namespace cv;

void ControlSim::operator()()
{
  steady_clock::time_point start = steady_clock::now();

  steady_clock::time_point end = steady_clock::now();
  duration<double> time_span = duration_cast<duration<double>>(end - start);

  cout << "[CONTROL] Frame received (" << time_span.count() * 1000 << "ms).\n";
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