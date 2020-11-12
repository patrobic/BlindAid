#pragma once

#include "Capture.h"
#include "Record.h"
#include "Vision.h"
#include "Control.h"
#include "Display.h"

namespace Core
{
  class Data : public IData
  {
  public:
    Data(Parameters *params)
    {
      _captureResults = new Capture::Data();
      _recordResults = new Record::Data();
      _visionResults = new Vision::Data(params->GetVisionParams());
      _controlResults = new Control::Data();
      _displayResults = new Display::Data();
    }

    ~Data()
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

    Capture::Data *GetCaptureResults() { return _captureResults; }
    Record::Data *GetRecordResults() { return _recordResults; }
    Vision::Data *GetVisionResults() { return _visionResults; }
    Control::Data *GetControlResults() { return _controlResults; }
    Display::Data *GetDisplayResults() { return _displayResults; }

  private:
    Capture::Data *_captureResults;
    Record::Data *_recordResults;
    Vision::Data *_visionResults;
    Control::Data *_controlResults;
    Display::Data *_displayResults;
  };
}