#include "Vision.h"

using namespace std;
using namespace std::chrono;
using namespace cv;

namespace Vision
{
  Vision::Vision(IParameters *params, IData *input, IData *output) : IModule(params, input, output)
  {
    CreateModules();
  }

  void Vision::CreateModules()
  {
    _depthObstacle = DepthObstacle::Base::MakeDepthObstacle(_params->GetDepthObstacleParams(), _input, _output->GetDepthObstacleResults());
    _trafficLight = TrafficLight::Base::MakeTrafficLight(_params->GetTrafficLightParams(), _input, _output->GetTrafficLightResults());
    _stopSign = new StopSign::Base(_params->GetStopSignParams(), _input, _output->GetStopSignResults());
  }

  void Vision::Process()
  {
    steady_clock::time_point start = steady_clock::now();

    (*_depthObstacle)();
    (*_trafficLight)();
    (*_stopSign)();

    steady_clock::time_point end = steady_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(end - start);

    cout << "[ VISION] Frame detected (" << time_span.count() * 1000 << "ms).\n";
  }
}