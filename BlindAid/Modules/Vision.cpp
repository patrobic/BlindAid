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
    _depthObstacle = new DepthObstacle::Detect(_params->GetDepthObstacleParams(), _input, _output->GetDepthObstacleResults());
    _trafficLight = TrafficLight::Base::MakeTrafficLight(_params->GetTrafficLightParams(), _input, _output->GetTrafficLightResults());
    _stopSign = new StopSign::Detect(_params->GetStopSignParams(), _input, _output->GetStopSignResults());

    _output->SetCurrentColorImage(_input->GetRgbImage());
    _output->SetCurrentDepthImage(_input->GetDepthImage());
  }

  void Vision::Process()
  {
    steady_clock::time_point start = steady_clock::now();

    (*_stopSign)();
    (*_trafficLight)();
    (*_depthObstacle)();

    steady_clock::time_point end = steady_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(end - start);

    cout << "[VISION ] Frame detected (" << time_span.count() * 1000 << "ms).\n";
  }
}