#include "Vision.h"

using namespace std;
using namespace std::chrono;
using namespace cv;

#define NAME "VISION"

namespace Vision
{
  Vision::Vision(IParameters *params, IData *input, IData *output, Tools::Logger *logger) : IModule(params, input, output, logger)
  {
    _depthObstacle = DepthObstacle::Base::MakeDepthObstacle(_params->GetDepthObstacleParams(), _input, _output->GetDepthObstacleResults(), _logger);
    _trafficLight = TrafficLight::Base::MakeTrafficLight(_params->GetTrafficLightParams(), _input, _output->GetTrafficLightResults(), _logger);
  }

  Vision::~Vision()
  {
    delete _depthObstacle;
    delete _trafficLight;
  }

  void Vision::Process()
  {
    _start = steady_clock::now();

    RunModules();

    LOG(Tools::Info, "Image detection processed", _start);
  }

  void Vision::RunModules()
  {
    if ((_params->GetGlobalParameters()->GetType() & Depth) == Depth)
      (*_depthObstacle)();

    if ((_params->GetGlobalParameters()->GetType() & Color) == Color)
      (*_trafficLight)();
  }
}