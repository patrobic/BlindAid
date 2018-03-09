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
      //PrintStopSign();

      steady_clock::time_point end = steady_clock::now();
      duration<double> time_span = duration_cast<duration<double>>(end - start);
      cout << "[CONTROL] Control displayed on screen.\t(" << setw(5) << (int)(time_span.count() * 1000) << "ms).\n";
    }

    void Simulate::PrintDepthObstacle()
    {
      cout << "  [GLOVE] (";
      for (int i = 0; i < 5; ++i)
        cout << _input->GetDepthObstacleResults()->_names[i].substr(0, 2) << "=" << (int)_input->GetDepthObstacleResults()->GetVibration(i)->Get() << " ";
      cout << ").\n";
    }

    void Simulate::PrintTrafficLights()
    {
      stringstream lights;

      cout << "  [AUDIO] ";
      if (_input->GetTrafficLightResults()->GetAll()->at(0).GetCenter() == Point(0, 0))
      {
        for (int i = 0; i < 4; ++i)
          lights << _input->GetTrafficLightResults()->_names[i].substr(0, 2) << "=" << fixed << setprecision(1) << _input->GetTrafficLightResults()->GetConfidence((Vision::TrafficLight::Result::Color)i) * 100 << "% ";
        cout << _input->GetTrafficLightResults()->_names[_input->GetTrafficLightResults()->GetColor()] << " (" << lights.str() << ").\n";
      }
      else
      {
        for (int i = 0; i < _input->GetTrafficLightResults()->Get().size(); ++i)
          lights << _input->GetTrafficLightResults()->_names[_input->GetTrafficLightResults()->GetAll()->at(i).GetColor()].substr(0, 2) << ", ";
        cout << " TrafficLights(" << lights.str() << "Total: " << _input->GetTrafficLightResults()->Get().size() << ").\n";
      }

    }

    void Simulate::PrintStopSign()
    {
      int stopSignCount = _input->GetStopSignResults()->GetRegion()._radius > 0 ? 1 : 0;
      if (stopSignCount > 0) cout << " StopSign(" << stopSignCount << ")"; cout << ".\n";
    }
  }
}