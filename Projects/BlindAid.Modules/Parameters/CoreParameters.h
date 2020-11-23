#pragma once

#include "Capture.h"
#include "Record.h"
#include "Vision.h"
#include "Control.h"
#include "Display.h"

namespace Core
{
  class CoreParameters : public SwitchableParameters
  {
  public:
    CoreParameters(GlobalParameters *params) : SwitchableParameters(params), _captureParams(params), _recordParams(params), _visionParams(params), _controlParams(params), _displayParams(params)
    {
      Defaults();
    }

    void Defaults()
    {
      _mode = Simulate;

      _consoleWindowPosition = cv::Point(0, 360);
      _consoleWindowScale = 1.f;
    }

    bool Valid()
    {
      return true;
    }

    Capture::CaptureParameters *GetCaptureParams() { return &_captureParams; }
    Record::RecordParameters *GetRecordParams() { return &_recordParams; }
    Vision::VisionParameters *GetVisionParams() { return &_visionParams; }
    Control::ControlParameters *GetControlParams() { return &_controlParams; }
    Display::DisplayParameters *GetDisplayParams() { return &_displayParams; }

    cv::Point GetConsoleWindowPosition() { return _consoleWindowPosition; }
    void SetConsoleWindowPosition(cv::Point point) { _consoleWindowPosition = point; }

    float GetConsoleWindowScale() { return _consoleWindowScale; }
    void SetConsoleWindowScale(float scale) { _consoleWindowScale = scale; }


  private:
    Capture::CaptureParameters _captureParams;
    Record::RecordParameters _recordParams;
    Vision::VisionParameters _visionParams;
    Control::ControlParameters _controlParams;
    Display::DisplayParameters _displayParams;

    // position of console window.
    cv::Point _consoleWindowPosition;

    // scale of console window.
    float _consoleWindowScale;
  };
}