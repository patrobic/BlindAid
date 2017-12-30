#include "ControlSimulate.h"

#include <iomanip>

using namespace std;
using namespace std::chrono;
using namespace cv;

namespace Control
{
  namespace Simulate
  {
    Simulate::Simulate(IParameters *params, IData *input, IData *output) : Base(params, input, output)
    {
      _vibration = Mat(1, 5, CV_8UC1);
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

      cout << "  [GLOVE] Thumb, Index, Middle, Ring, Pinky (";
      for (int i = 0; i < 5; ++i)
      {
        cout << setw(4) << (int)_vibrationIntensity[i]->Get();
        _vibration.at<uchar>(Point(i, 0)) = (int)_vibrationIntensity[i]->Get();
      }
      cout << ").\n";

      namedWindow("Vibration Image", WINDOW_NORMAL);
      moveWindow("Vibration Image", _params->GetSimulateParams()->GetVibrationWindowPosition().x, _params->GetSimulateParams()->GetVibrationWindowPosition().y);
      resizeWindow("Vibration Image", (int)_params->GetSimulateParams()->GetVibrationWindowScale() * 5, (int)_params->GetSimulateParams()->GetVibrationWindowScale());
      imshow("Vibration Image", _vibration);
      waitKey(1);
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