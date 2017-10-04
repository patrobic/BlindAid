#include "ModuleCore.h"

void Core::Init(Data *data, IParameters *params, IResults *input, IResults *output)
{
  _data = data;
  _params = static_cast<Parameters*>(params);
  _input = static_cast<Results*>(output);
  _output = static_cast<Results*>(output);

  // TODO: Initialize hardware capture & control.
}

void Core::operator()()
{
  _vision = new Vision();
  if (_params->GetCaptureMode() == Parameters::Mode::Realtime) _capture = new Capture();
  else _capture = new CaptureSim();
  _display = new Display();
  if (_params->GetControlMode() == Parameters::Mode::Realtime) _control = new Control();
  else _control = new ControlSim();

  _capture->Init(_data, _params->GetCaptureParams(), NULL, _output->GetCaptureResults());
  _vision->Init(_data, _params->GetVisionParams(), _output->GetCaptureResults(), _output->GetVisionResults());
  _control->Init(_data, _params->GetCaptureParams(), _output->GetVisionResults(), NULL);
  _display->Init(_data, _params->GetDisplayParams(), _output->GetVisionResults(), _output->GetCaptureResults()); // note: uses CaptureResults as "output" even though it is technically an input.

  (*_capture)();
  (*_vision)();
  (*_control)();
  (*_display)();

  _data->_captureThread.join();
  _data->_visionThread.join();
  _data->_controlThread.join();
  _data->_displayThread.join();

  delete _capture;
  delete _vision;
  delete _control;
  delete _display;
}