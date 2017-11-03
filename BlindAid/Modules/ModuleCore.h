#pragma once

#include "ModuleCapture.h"
#include "ModuleVision.h"
#include "ModuleControl.h"
#include "ModuleDisplay.h"

#include "SimulateCapture.h"
#include "SimulateControl.h"

class Core : public IModule
{
public:
  class Parameters : public IParameters
  {
  public:
    Capture::Parameters *GetCaptureParams() { return &_captureParams; }
    Vision::Parameters *GetVisionParams() { return &_visionParams; }
    Control::Parameters *GetControlParams() { return &_controlParams; }
    Display::Parameters *GetDisplayParams() { return &_displayParams; }

  private:
    Capture::Parameters _captureParams;
    Vision::Parameters _visionParams;
    Control::Parameters _controlParams;
    Display::Parameters _displayParams;
  };

  class Data : public IData
  {
  public:
    void Clear() {}

    Capture::Data *GetCaptureResults() { return &_captureResults; }
    Vision::Data *GetVisionResults() { return &_visionResults; }
    Control::Data *GetControlResults() { return &_controlResults; }
    Display::Data *GetDisplayResults() { return &_displayResults; }

  private:
    Capture::Data _captureResults;
    Vision::Data _visionResults;
    Control::Data _controlResults;
    Display::Data _displayResults;
  };

  Core(IParameters *params, IData *input, IData *output);
  void operator()();

private:
  Parameters *_params;
  Data *_input;
  Data *_output;

  // capture and control declared as base class pointer so that it can be declared based on parameter as either simulate or realtime class.
  IModule *_capture;
  Vision *_vision;
  IModule *_control;
  Display *_display;
};