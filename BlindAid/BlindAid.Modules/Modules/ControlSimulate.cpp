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
    ControlSimulate::ControlSimulate(IParameters *params, IData *input, IData *output, Logger *logger) : Control(params, input, output, logger)
    {

    }

    ControlSimulate::~ControlSimulate()
    {

    }

    void ControlSimulate::Process()
    {
      _start = steady_clock::now();
      
      PrintResults();

      LOG(Info, "Control values displayed on screen", "SIMULATE", _start);
    }

    void ControlSimulate::PrintResults()
    {
      if ((_params->GetGlobalParameters()->GetType() & Color) == Color)
        PrintTrafficLights();
      if ((_params->GetGlobalParameters()->GetType() & Depth) == Depth)
        PrintDepthObstacle();
    }
    void ControlSimulate::PrintDepthObstacle()
    {
        stringstream ss;
        ss << "Vibration values (";
        for (int i = 0; i < 5; ++i)
          ss << _input->GetDepthObstacleResults()->_names[i].substr(0, 2) << "=" << (int)_input->GetDepthObstacleResults()->GetVibration(i) << " ";
        ss << ")";

        LOG(Info, ss.str(), "GLOVE");
    }

    void ControlSimulate::PrintTrafficLights()
    {
      stringstream lights;
      stringstream ss;
      ss << "Traffic light color ";

      _input->GetTrafficLightResults()->_trafficLightMutex.lock();

      if (_input->GetTrafficLightResults()->GetAll()->size() > 0 && _input->GetTrafficLightResults()->GetAll()->at(0).GetCenter() == Point(0, 0))
      {
        for (int i = 0; i < 4; ++i)
          lights << _input->GetTrafficLightResults()->_names[i].substr(0, 2) << "=" << fixed << setprecision(1) << _input->GetTrafficLightResults()->GetConfidence((Vision::TrafficLight::TrafficLightResult::Color)i) * 100 << "% ";
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
  }
}