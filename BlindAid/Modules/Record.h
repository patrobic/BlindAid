#pragma once

#include "IModule.h"
#include "CaptureBase.h"

namespace Record
{
  class Parameters : public IParameters
  {
  public:
    enum Type
    {
      Color,
      Depth,
      Both
    };

    bool Valid()
    {
      return true;
    }

  private:
    // path at which to save image stream.
    std::string _path;

    // save color, depth, or both
    Type _type;
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

  private:
    void Process();
    void SaveToDisk();

    Parameters *_params;
    Capture::Data *_input;
    Data *_output;
  };
}