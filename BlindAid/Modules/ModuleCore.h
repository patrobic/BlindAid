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
    enum Mode
    {
      Simulate,
      Realtime
    };

    Mode GetCaptureMode() { return _captureMode; }
    void SetCaptureMode(Mode captureMode) { _captureMode = captureMode; }
    Mode GetControlMode() { return _controlMode; }
    void SetControlMode(Mode controlMode) { _controlMode = controlMode; }

    bool GetEnableDisplay() { return _enableDisplay; }
    void SetEnableDisplay(bool enableDisplay) { _enableDisplay = enableDisplay; }

    Capture::Parameters *GetCaptureParams() { return &_captureParams; }
    Vision::Parameters *GetVisionParams() { return &_visionParams; }
    Control::Parameters *GetControlParams() { return &_controlParams; }
    Display::Parameters *GetDisplayParams() { return &_displayParams; }

  private:
    Mode _captureMode = Realtime;
    Mode _controlMode = Realtime;

    bool _enableDisplay = false;

    Capture::Parameters _captureParams;
    Vision::Parameters _visionParams;
    Control::Parameters _controlParams;
    Display::Parameters _displayParams;
  };

  class Results : public IResults
  {
  public:
    void Clear() {}

    Capture::Results *GetCaptureResults() { return &_captureResults; }
    Vision::Results *GetVisionResults() { return &_visionResults; }
    Control::Results *GetControlResults() { return &_controlResults; }
    Display::Results *GetDisplayResults() { return &_displayResults; }

  private:
    Capture::Results _captureResults;
    Vision::Results _visionResults;
    Control::Results _controlResults;
    Display::Results _displayResults;

  };

  Core(Data *data, IParameters *params, IResults *input, IResults *output);
  void operator()();

private:
  Parameters *_params;
  Results *_input;
  Results *_output;

  IModule *_capture;
  Vision *_vision;
  IModule *_control;
  Display *_display;
};