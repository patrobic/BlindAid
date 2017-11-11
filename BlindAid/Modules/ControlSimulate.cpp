#include "ControlSimulate.h"

using namespace std;
using namespace std::chrono;
using namespace cv;

namespace Control
{
  Simulate::Simulate(IParameters *params, IData *input, IData *output) : Base(params, input, output)
  {

  }

  void Simulate::Process()
  {
    steady_clock::time_point start = steady_clock::now();

    steady_clock::time_point end = steady_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(end - start);

    cout << "[CONTROL] Frame received (" << time_span.count() * 1000 << "ms).\n";
    cout << "\t[GLOVE] \
Thumb(" << CalculateVibrationValue(_input->GetDepthObstacleResults()->GetMinColIntensity(0)) << "), \
Index(" << CalculateVibrationValue(_input->GetDepthObstacleResults()->GetMinColIntensity(1)) << "), \
Middle(" << CalculateVibrationValue(_input->GetDepthObstacleResults()->GetMinColIntensity(2)) << "), \
Ring(" << CalculateVibrationValue(_input->GetDepthObstacleResults()->GetMinColIntensity(3)) << "), \
Pinky(" << CalculateVibrationValue(_input->GetDepthObstacleResults()->GetMinColIntensity(4)) << "), \
Upper(" << CalculateVibrationValue(_input->GetDepthObstacleResults()->GetMinRowIntensity(0)) << "), \
Lower(" << CalculateVibrationValue(_input->GetDepthObstacleResults()->GetMinRowIntensity(2)) << ").\n";

    cout << "\t[AUDIO]";

    int trafficLightCount = _input->GetTrafficLightResults()->Size();
    string name[3] = { "Red", "Green", "Yellow" };
    stringstream lights;
    for (int i = 0; i < trafficLightCount; ++i)
      lights << name[_input->GetTrafficLightResults()->At(i)._color] << ", ";
    if (trafficLightCount > 0) cout << " TrafficLights(" << lights.str() << "Total: " << trafficLightCount << ")";

    int stopSignCount = _input->GetStopSignResults()->GetRegion()._radius > 0 ? 1 : 0;
    if (stopSignCount > 0) cout << " StopSign(" << trafficLightCount << ")"; cout << ".\n";
  }
}