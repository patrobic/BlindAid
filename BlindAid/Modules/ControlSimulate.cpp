#include "ControlSimulate.h"

using namespace std;
using namespace std::chrono;
using namespace cv;

namespace Control
{
  namespace Simulate
  {
    Simulate::Simulate(IParameters *params, IData *input, IData *output) : Base(params, input, output)
    {

    }

    void Simulate::Process()
    {
      steady_clock::time_point start = steady_clock::now();

      MapVibrationValues();
      PrintDepthObstacle();
      PrintTrafficLights();
      PrintStopSign();

      steady_clock::time_point end = steady_clock::now();
      duration<double> time_span = duration_cast<duration<double>>(end - start);
      cout << "[CONTROL] Frame executed (" << time_span.count() * 1000 << "ms).\n";
   }

    void Simulate::PrintDepthObstacle()
    {
      string signals[7] = { "Thumb", "Index", "Middle", "Ring", "Pinky", "Option1", "Option2" };

      cout << "  [GLOVE] ";
      for (int i = 0; i < 5; ++i)
        cout << signals[i] << "(" << _vibrationIntensity[0] << "), ";
      cout << endl;
    }

    void Simulate::PrintTrafficLights()
    {
      string name[3] = { "Red", "Green", "Yellow" };
      stringstream lights;
      int trafficLightCount = _input->GetTrafficLightResults()->Size();

      cout << "  [AUDIO] ";
      for (int i = 0; i < trafficLightCount; ++i)
        lights << name[_input->GetTrafficLightResults()->At(i)._color] << ", ";
      if (trafficLightCount > 0) cout << " TrafficLights(" << lights.str() << "Total: " << trafficLightCount << ")";
    }

    void Simulate::PrintStopSign()
    {
      int stopSignCount = _input->GetStopSignResults()->GetRegion()._radius > 0 ? 1 : 0;
      if (stopSignCount > 0) cout << " StopSign(" << stopSignCount << ")"; cout << ".\n";
    }
  }
}