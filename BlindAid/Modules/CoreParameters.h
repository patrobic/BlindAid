#pragma once

#include "Capture.h"
#include "Record.h"
#include "Vision.h"
#include "Control.h"
#include "Display.h"

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
}