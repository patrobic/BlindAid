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

    }

    void Simulate::Process()
    {
      steady_clock::time_point start = steady_clock::now();

      PrintDepthObstacle();
      PrintTrafficLights();
      PrintStopSign();

      steady_clock::time_point end = steady_clock::now();
      duration<double> time_span = duration_cast<duration<double>>(end - start);
      cout << "[CONTROL] Control data displayed on screen (" << setw(5) << (int)(time_span.count() * 1000) << "ms).\n";
    }

    void Simulate::PrintDepthObstacle()
    {
      cout << "  [GLOVE] Thumb, Index, Middle, Ring, Pinky (";
      for (int i = 0; i < 5; ++i)
        cout << setw(4) << (int)_input->GetDepthObstacleResults()->GetVibration(i)->Get();
      cout << ").\n";
    }
    
    void Simulate::PrintTrafficLights()
    {
      stringstream lights;
      vector<Vision::TrafficLight::Result> result = _input->GetTrafficLightResults()->Get();

      cout << "  [AUDIO] ";
      if (result.size() == 1 && result.at(0).GetCenter() == Point(0, 0))
        cout << _input->GetTrafficLightResults()->_names[result.at(0).GetColor()] << " (" << setprecision(3) << result.at(0).GetConfidence(result.at(0).GetColor()) * 100 << "%).\n";
        //"Red, Green, None (" << result.at(0).GetConfidence((Vision::TrafficLight::Result::Color)0) << ", " << result.at(0).GetConfidence((Vision::TrafficLight::Result::Color)1) << ", " << result.at(0).GetConfidence((Vision::TrafficLight::Result::Color)2) << ").\n";
      else
      {

        for (int i = 0; i < result.size(); ++i)
          lights << _input->GetTrafficLightResults()->_names[_input->GetTrafficLightResults()->GetAll()->at(i).GetColor()] << ", ";
        if (result.size() > 0) cout << " TrafficLights(" << lights.str() << "Total: " << result.size() << ")";
      }
    }

    void Simulate::PrintStopSign()
    {
      int stopSignCount = _input->GetStopSignResults()->GetRegion()._radius > 0 ? 1 : 0;
      if (stopSignCount > 0) cout << " StopSign(" << stopSignCount << ")"; cout << ".\n";
    }
  }
}