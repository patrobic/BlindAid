#pragma once

#include "RecordParameters.h"
#include "IModule.h"
#include "Vision.h"
#include "Capture.h"
#include "RecordData.h"

namespace Record
{
  class Record : public IModule<RecordParameters, Vision::VisionData, Capture::CaptureData>
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