#include "ModuleCore.h"

using namespace std;
using namespace std::chrono;
using namespace cv;

Core::Core(IParameters *params, IData *input, IData *output)
{
  _params = static_cast<Parameters*>(params);
  _input = static_cast<Data*>(output);
  _output = static_cast<Data*>(output);
}

void Core::operator()()
{  
  if (_params->GetCaptureParams()->GetMode() == Parameters::Mode::Realtime)
    _capture = new Capture(_params->GetCaptureParams(), NULL, _output->GetCaptureResults());
  else
    _capture = new CaptureSim(_params->GetCaptureParams(), NULL, _output->GetCaptureResults());
  
  _vision = new Vision(_params->GetVisionParams(), _output->GetCaptureResults(), _output->GetVisionResults());
  
  if (_params->GetControlParams()->GetMode() == Parameters::Mode::Realtime)
    _control = new Control(_params->GetDisplayParams(), _output->GetVisionResults(), _output->GetCaptureResults());
  else
    _control = new ControlSim(_params->GetDisplayParams(), _output->GetVisionResults(), _output->GetCaptureResults());
  
  if (_params->GetDisplayParams()->GetToggle() == Parameters::Toggle::Enabled)
    _display = new Display(_params->GetDisplayParams(), _output->GetVisionResults(), _output->GetCaptureResults());

  int frame = 0;

  do
  {
    steady_clock::time_point start = steady_clock::now();

    (*_capture)();
    (*_vision)();
    (*_control)();

    if(_params->GetDisplayParams()->GetToggle() == IParameters::Toggle::Enabled)
      (*_display)();

    steady_clock::time_point end = steady_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(end - start);

    cout << "[CORE] Frame #" << to_string(frame++) << " processed (" << time_span.count() * 1000 << "ms).\n";
  }
  while (_params->GetCaptureParams()->GetMediaType() == Capture::Parameters::MediaType::Video);

  delete _capture;
  delete _vision;
  delete _control;
  delete _display;
}