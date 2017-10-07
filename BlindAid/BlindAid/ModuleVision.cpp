#include "ModuleVision.h"

using namespace std;
using namespace std::chrono;
using namespace cv;

Vision::Vision(Data *data, IParameters *params, IResults *input, IResults *output) :
  _depthObstacle(data, static_cast<Parameters*>(params)->GetDepthObstacleParams(), input, static_cast<Results*>(output)->GetDepthObstacleResults()),
  _trafficLight(data, static_cast<Parameters*>(params)->GetTrafficLightParams(), input, static_cast<Results*>(output)->GetTrafficLightResults()),
  _stopSign(data, static_cast<Parameters*>(params)->GetStopSignParams(), input, static_cast<Results*>(output)->GetStopSignResults())
{
  _data = data;
  _params = static_cast<Parameters*>(params);
  _input = static_cast<CaptureSim::Results*>(input);
  _output = static_cast<Results*>(output);
}

void Vision::operator()()
{
  steady_clock::time_point start = steady_clock::now();
 
  _output->SetCurrentColorImage(_input->GetColorImage());
  _output->SetCurrentDepthImage(_input->GetDepthImage());
  
  if (_params->GetStopSignParams()->GetToggle() == Parameters::Toggle::Enabled) _stopSign();
  if (_params->GetTrafficLightParams()->GetToggle() == Parameters::Toggle::Enabled) _trafficLight();
  if (_params->GetDepthObstacleParams()->GetToggle() == Parameters::Toggle::Enabled) _depthObstacle();

  steady_clock::time_point end = steady_clock::now();
  duration<double> time_span = duration_cast<duration<double>>(end - start);

  cout << "[VISION] Frame detected (" << time_span.count() * 1000 << "ms).\n";
}