#pragma once

#include "IModule.h"
#include "Vision.h"
#include "Capture.h"

namespace Record
{
  class Parameters : public SwitchableParameters
  {
  public:
    Parameters(GlobalParameters *params) : SwitchableParameters(params)
    {
      Defaults();
    }

    void Defaults()
    {
      _path = "C:\\BlindAidRecord\\";
      _manualTrigger = true;

      _toggle = Disabled;
    }

    bool Valid()
    {
      return true;
    }

    std::string GetPath() { return _path; }
    void SetPath(std::string path) { _path = path; }

    bool GetManualTrigger() { return _manualTrigger; }
    void SetManualTrigger(bool manualTrigger) { _manualTrigger = manualTrigger; }

  private:
    // path at which to save image stream.
    std::string _path;

    // set whether images are captured continuously or on demand.
    bool _manualTrigger;
  };

  class Data : public IData
  {
  public:
    void Clear() {}
    bool Valid()
    {
      return true;
    }

  private:

  };

  class Record : public IModule<Parameters, Vision::Data, Capture::Data>
  {
  public:
    Record(IParameters *params, IData *input, IData *output, Logger *logger);

    void CreateFolder();

  private:
    void Process();
    void SaveToDisk();

    std::string _folderName;
    int _index = 0;
    bool _firstRun = true;
  };
}