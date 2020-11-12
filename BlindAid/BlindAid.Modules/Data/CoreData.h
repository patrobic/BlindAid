#pragma once

#include "Capture.h"
#include "Record.h"
#include "Vision.h"
#include "Control.h"
#include "Display.h"

namespace Core
{
  class CoreData : public IData
  {
  public:
    CoreData(CoreParameters *params)
    {
      _captureResults = new Capture::CaptureData();
      _recordResults = new Record::RecordData();
      _visionResults = new Vision::VisionData(params->GetVisionParams());
      _controlResults = new Control::ControlData();
      _displayResults = new Display::DisplayData();
    }

    ~CoreData()
    {
      delete _captureResults;
      delete _recordResults;
      delete _visionResults;
      delete _controlResults;
      delete _displayResults;
    }

    void Clear()
    {
    
    }
    
    bool Valid()
    {
      return true;
    }

    Capture::CaptureData *GetCaptureResults() { return _captureResults; }
    Record::RecordData *GetRecordResults() { return _recordResults; }
    Vision::VisionData *GetVisionResults() { return _visionResults; }
    Control::ControlData *GetControlResults() { return _controlResults; }
    Display::DisplayData *GetDisplayResults() { return _displayResults; }

  private:
    Capture::CaptureData *_captureResults;
    Record::RecordData *_recordResults;
    Vision::VisionData *_visionResults;
    Control::ControlData *_controlResults;
    Display::DisplayData *_displayResults;
  };
}