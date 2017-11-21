#pragma once

#include "IModule.h"
#include "Capture.h"

namespace Record
{
  class Parameters : public SwitchableParameters
  {
  public:
    Parameters() { Defaults(); }

    void Defaults()
    {
      _path = "";
    }

    bool Valid()
    {
      return true;
    }

    std::string GetPath() { return _path; }
    void SetPath(std::string path) { _path = path; }

  private:
    // path at which to save image stream.
    std::string _path;
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

  class Record : public IModule<Parameters, Capture::Data, Data>
  {
  public:

    Record(IParameters *params, IData *input, IData *output);

    void CreateFolder();

  private:
    void Process();
    void SaveToDisk();

    std::string _folderName;
    int _index = 0;
  };
}