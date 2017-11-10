#pragma once

#include "ModuleCapture.h"
#include "ModuleRecord.h"
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
    Record::Parameters *GetRecordParams() { return &_recordParams; }
    Vision::Parameters *GetVisionParams() { return &_visionParams; }
    Control::Parameters *GetControlParams() { return &_controlParams; }
    Display::Parameters *GetDisplayParams() { return &_displayParams; }

    int GetRepeat() { return _repeat; }
    void SetRepeat(int repeat) { _repeat = repeat; }

  private:
    Capture::Parameters _captureParams;
    Record::Parameters _recordParams;
    Vision::Parameters _visionParams;
    Control::Parameters _controlParams;
    Display::Parameters _displayParams;

    int _repeat = 0;
  };

  class Data : public IData
  {
  public:
    void Clear() {}

    Capture::Data *GetCaptureResults() { return &_captureResults; }
    Record::Data *GetRecordResults() { return &_recordResults; }
    Vision::Data *GetVisionResults() { return &_visionResults; }
    Control::Data *GetControlResults() { return &_controlResults; }
    Display::Data *GetDisplayResults() { return &_displayResults; }

  private:
    Capture::Data _captureResults;
    Record::Data _recordResults;
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
  Record *_record;
  Vision *_vision;
  IModule *_control;
  Display *_display;
};