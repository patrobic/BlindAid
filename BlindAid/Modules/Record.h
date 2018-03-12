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
      _path = "C:\\Record\\";
      _interval = 0;

      _toggle = Disabled;
    }

    bool Valid()
    {
      return true;
    }

    std::string GetPath() { return _path; }
    void SetPath(std::string path) { _path = path; }

    int GetInterval() { return _interval; }
    void SetInterval(int interval) { _interval = interval; }

  private:
    // path at which to save image stream.
    std::string _path;

    // set whether images are captured continuously or on demand.
    int _interval;
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