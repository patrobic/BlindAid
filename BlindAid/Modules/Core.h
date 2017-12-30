#pragma once

#include "Capture.h"
#include "Record.h"
#include "Vision.h"
#include "Control.h"
#include "Display.h"

#include "CaptureSimulate.h"
#include "ControlSimulate.h"

namespace Core
{
  class Parameters : public SwitchableParameters
  {
  public:
    Parameters() { Defaults(); }

    void Defaults()
    {
      _captureParams.Defaults();
      _recordParams.Defaults();
      _visionParams.Defaults();
      _controlParams.Defaults();
      _displayParams.Defaults();

      _mode = Simulate;
      _repeat = 0;

      _consoleWindowPosition = cv::Point(0, 300);
      _consoleWindowScale = 1.f;
    }

    bool Valid()
    {
      return true;
    }

    Capture::Parameters *GetCaptureParams() { return &_captureParams; }
    Record::Parameters *GetRecordParams() { return &_recordParams; }
    Vision::Parameters *GetVisionParams() { return &_visionParams; }
    Control::Parameters *GetControlParams() { return &_controlParams; }
    Display::Parameters *GetDisplayParams() { return &_displayParams; }

    Mode GetMode() { return _mode; }
    void SetMode(Mode mode) { _mode = mode; }

    int GetRepeat() { return _repeat; }
    void SetRepeat(int repeat) { _repeat = repeat; }
 
    cv::Point GetConsoleWindowPosition() { return _consoleWindowPosition; }
    void SetConsoleWindowPosition(cv::Point point) { _consoleWindowPosition = point; }

    float GetConsoleWindowScale() { return _consoleWindowScale; }
    void SetConsoleWindowScale(float scale) { _consoleWindowScale = scale; }

  private:
    Capture::Parameters _captureParams;
    Record::Parameters _recordParams;
    Vision::Parameters _visionParams;
    Control::Parameters _controlParams;
    Display::Parameters _displayParams;

    Mode _mode;

    // max number of times to run the detection loop.
    int _repeat;

    // position of console window.
    cv::Point _consoleWindowPosition;

    // scale of console window.
    float _consoleWindowScale;

  };

  class Data : public IData
  {
  public:
    void Clear() {}
    bool Valid()
    {
      return true;
    }

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

  class Core : public IModule<Parameters, Data, Data>
  {
  public:
    Core(IParameters *params, IData *input, IData *output);

  private:
    void Process();
    void CreateModules();

    // capture and control declared as base class pointer so that it can be declared based on parameter as either simulate or realtime class.
    Capture::Base *_capture;
    Record::Record *_record;
    Vision::Vision *_vision;
    Control::Base *_control;
    Display::Display *_display;

    int _frame = 0;
  };
}