#include "Vision.h"

using namespace std;
using namespace std::chrono;
using namespace cv;

#define NAME "VISION"

namespace Vision
{
  Vision::Vision(IParameters *params, IData *input, IData *output, Logger *logger) : IModule(params, input, output, logger)
  {
    CreateModules();
  }

  void Vision::CreateModules()
  {
    _depthObstacle = DepthObstacle::Base::MakeDepthObstacle(_params->GetDepthObstacleParams(), _input, _output->GetDepthObstacleResults(), _logger);
    _trafficLight = TrafficLight::Base::MakeTrafficLight(_params->GetTrafficLightParams(), _input, _output->GetTrafficLightResults(), _logger);
  }

  void Vision::Process()
  {
    _start = steady_clock::now();

    RunModules();

    LOG(Info, "Image detection processed", _start);
  }

  void Vision::RunModules()
  {
    if (_params->GetGlobalParameters()->GetType() == Depth || _params->GetGlobalParameters()->GetType() == Both)
      (*_depthObstacle)();

    if (_params->GetGlobalParameters()->GetType() == Color || _params->GetGlobalParameters()->GetType() == Both)
      (*_trafficLight)();
  }
}