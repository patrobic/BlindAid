#pragma once

#include "RecordParams.h"
#include "IModule.h"
#include "Vision.h"
#include "Capture.h"

namespace Record
{
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