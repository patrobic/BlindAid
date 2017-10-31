#include "ModuleCore.h"

using namespace std;
using namespace std::chrono;
using namespace cv;

Core::Core(Data *data, IParameters *params, IResults *input, IResults *output)
{
  _data = data;
  _params = static_cast<Parameters*>(params);
  _input = static_cast<Results*>(output);
  _output = static_cast<Results*>(output);

  // TODO: Initialize hardware capture & control.
}

void Core::operator()()
{
  int frame = 0;

  _vision = new Vision(_data, _params->GetVisionParams(), _output->GetCaptureResults(), _output->GetVisionResults());
  
  if (_params->GetCaptureMode() == Parameters::Mode::Realtime)
    _capture = new Capture(_data, _params->GetCaptureParams(), NULL, _output->GetCaptureResults());
  else
    _capture = new CaptureSim(_data, _params->GetCaptureParams(), NULL, _output->GetCaptureResults());

  _display = new Display(_data, _params->GetDisplayParams(), _output->GetVisionResults(), _output->GetCaptureResults());
  
  if (_params->GetControlMode() == Parameters::Mode::Realtime)
    _control = new Control(_data, _params->GetDisplayParams(), _output->GetVisionResults(), _output->GetCaptureResults());
  else
    _control = new ControlSim(_data, _params->GetDisplayParams(), _output->GetVisionResults(), _output->GetCaptureResults());

  do
  {
    steady_clock::time_point start = steady_clock::now();

    (*_capture)();

    if (_data->_run == false)
      break;

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