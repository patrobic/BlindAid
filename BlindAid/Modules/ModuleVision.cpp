#include "ModuleVision.h"

using namespace std;
using namespace std::chrono;
using namespace cv;

Vision::Vision(IParameters *params, IData *input, IData *output) :
  _depthObstacle(static_cast<Parameters*>(params)->GetDepthObstacleParams(), input, static_cast<Data*>(output)->GetDepthObstacleResults()),
  _trafficLight(static_cast<Parameters*>(params)->GetTrafficLightParams(), input, static_cast<Data*>(output)->GetTrafficLightResults()),
  _stopSign(static_cast<Parameters*>(params)->GetStopSignParams(), input, static_cast<Data*>(output)->GetStopSignResults())
{
  _params = static_cast<Parameters*>(params);
  _input = static_cast<CaptureSim::Data*>(input);
  _output = static_cast<Data*>(output);
}

void Vision::operator()()
{
  steady_clock::time_point start = steady_clock::now();
 
  _output->SetCurrentColorImage(_input->GetRgbImage());
  _output->SetCurrentDepthImage(_input->GetDepthImage());
  
  if (_params->GetStopSignParams()->GetToggle() == Parameters::Toggle::Enabled) _stopSign();
  if (_params->GetTrafficLightParams()->GetToggle() == Parameters::Toggle::Enabled) _trafficLight();
  if (_params->GetDepthObstacleParams()->GetToggle() == Parameters::Toggle::Enabled) _depthObstacle();

  steady_clock::time_point end = steady_clock::now();
  duration<double> time_span = duration_cast<duration<double>>(end - start);

  cout << "[VISION] Frame detected (" << time_span.count() * 1000 << "ms).\n";
}