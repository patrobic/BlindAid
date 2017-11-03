#pragma once

#include "IModule.h"
#include "ModuleCapture.h"

class Record : public IModule
{
public:
  class Parameters : public IParameters
  {
  public:
    enum Type
    {
      Color,
      Depth,
      Both
    };

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

  private:

  };

  Record(IParameters *params, IData *input, IData *output);
  void operator()();

private:
  void SaveToDisk();

  Parameters *_params;
  Capture::Data *_input;
  Data *_output;
};