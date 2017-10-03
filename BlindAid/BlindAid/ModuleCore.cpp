#include "ModuleCore.h"

void Core::Init(Data *data)
{
  _data = data;

  _data->_captureDone = false;
  _data->_visionDone = false;

  // TODO: Initialize hardware capture & control.
}

void Core::operator()()
{
  if (_data->_params.GetCaptureMode() == Parameters::Mode::Realtime)
    _capture = new Capture();
  else
    _capture = new CaptureSim();

  if (_data->_params.GetControlMode() == Parameters::Mode::Realtime)
    _control = new Control();
  else
    _control = new ControlSim();

  _capture->Init(_data);
  _vision.Init(_data);
  _control->Init(_data);
  _display.Init(_data);

  (*_capture)();
  _vision();
  (*_control)();
  _display();

  _data->_captureThread.join();
  _data->_visionThread.join();
  _data->_controlThread.join();
  _data->_displayThread.join();

  delete _capture;
  delete _control;
}