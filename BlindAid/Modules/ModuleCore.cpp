#include "ModuleCore.h"

using namespace std;
using namespace std::chrono;

Core::Core(IParameters *params, IData *input, IData *output)
{
  _params = static_cast<Parameters*>(params);
  _input = static_cast<Data*>(output);
  _output = static_cast<Data*>(output);

}

void Core::operator()()
{  
  static int frame = 0;

  if (_params->GetCaptureParams()->GetMode() == Parameters::Mode::Realtime)
    _capture = new Capture(_params->GetCaptureParams(), NULL, _output->GetCaptureResults());
  else
    _capture = new CaptureSim(_params->GetCaptureParams(), NULL, _output->GetCaptureResults());
  
  _record = new Record(_params->GetRecordParams(), _output->GetCaptureResults(), NULL);

  _vision = new Vision(_params->GetVisionParams(), _output->GetCaptureResults(), _output->GetVisionResults());
  
  if (_params->GetControlParams()->GetMode() == Parameters::Mode::Realtime)
    _control = new Control(_params->GetDisplayParams(), _output->GetVisionResults(), _output->GetCaptureResults());
  else
    _control = new ControlSim(_params->GetDisplayParams(), _output->GetVisionResults(), _output->GetCaptureResults());

  _display = new Display(_params->GetDisplayParams(), _output->GetVisionResults(), _output->GetCaptureResults());

  do
  {
    steady_clock::time_point start = steady_clock::now();

    if (_params->GetCaptureParams()->GetToggle())
      (*_capture)();
    
    if (_params->GetRecordParams()->GetToggle())
      (*_record)();

    if (_params->GetVisionParams()->GetToggle())
      (*_vision)();
 
    if (_params->GetControlParams()->GetToggle())
      (*_control)();

    if(_params->GetDisplayParams()->GetToggle())
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