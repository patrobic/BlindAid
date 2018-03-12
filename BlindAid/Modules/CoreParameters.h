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
    Parameters(GlobalParameters *params) : SwitchableParameters(params), _captureParams(params), _recordParams(params), _visionParams(params), _controlParams(params), _displayParams(params)
    {
      Defaults();
    }

    void Defaults()
    {
      _mode = SwitchableParameters::Mode::Simulate;
      _repeat = 1;

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

    // max number of times to run the detection loop.
    int _repeat;

    // position of console window.
    cv::Point _consoleWindowPosition;

    // scale of console window.
    float _consoleWindowScale;

  };
}