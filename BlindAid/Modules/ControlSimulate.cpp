#include "ControlSimulate.h"

#include <iomanip>

using namespace std;
using namespace std::chrono;
using namespace cv;

#define NAME "CONTROL"

namespace Control
{
  namespace Simulate
  {
    Simulate::Simulate(IParameters *params, IData *input, IData *output, Logger *logger) : Base(params, input, output, logger)
    {

    }

    void Simulate::Process()
    {
      _start = steady_clock::now();

      if (_params->GetType() == SwitchableParameters::Type::Depth || _params->GetType() == SwitchableParameters::Type::Both)
        PrintDepthObstacle();

      if (_params->GetType() == SwitchableParameters::Type::Color || _params->GetType() == SwitchableParameters::Type::Both)
        PrintTrafficLights();

      //PrintStopSign();

      LOG(Info, "Control values displayed on screen", "SIMULATE", _start);
    }

    void Simulate::PrintDepthObstacle()
    {
      stringstream ss;
      ss << "Vibration values (";
      for (int i = 0; i < 5; ++i)
        ss << _input->GetDepthObstacleResults()->_names[i].substr(0, 2) << "=" << (int)_input->GetDepthObstacleResults()->GetVibration(i)->Get() << " ";
      ss << ")";

      LOG(Info, ss.str(), "GLOVE");
    }

    void Simulate::PrintTrafficLights()
    {
      stringstream lights;
      stringstream ss;
      ss << "Traffic light color ";

      _input->GetTrafficLightResults()->_trafficLightMutex.lock();

      if (_input->GetTrafficLightResults()->GetAll()->at(0).GetCenter() == Point(0, 0))
      {
        for (int i = 0; i < 4; ++i)
          lights << _input->GetTrafficLightResults()->_names[i].substr(0, 2) << "=" << fixed << setprecision(1) << _input->GetTrafficLightResults()->GetConfidence((Vision::TrafficLight::Result::Color)i) * 100 << "% ";
        ss << _input->GetTrafficLightResults()->_names[_input->GetTrafficLightResults()->GetColor()] << " (" << lights.str() << ")";
      }
      else
      {
        for (int i = 0; i < _input->GetTrafficLightResults()->Get().size(); ++i)
          lights << _input->GetTrafficLightResults()->_names[_input->GetTrafficLightResults()->GetAll()->at(i).GetColor()].substr(0, 2) << ", ";
        ss << " TrafficLights(" << lights.str() << "Total: " << _input->GetTrafficLightResults()->Get().size() << ")";
      }

      LOG(Info, ss.str(), "AUDIO");

      _input->GetTrafficLightResults()->_trafficLightMutex.unlock();
    }

    void Simulate::PrintStopSign()
    {
      int stopSignCount = _input->GetStopSignResults()->GetRegion()._radius > 0 ? 1 : 0;
      if (stopSignCount > 0) cout << " StopSign(" << stopSignCount << ")"; cout << ".\n";
    }
  }
}