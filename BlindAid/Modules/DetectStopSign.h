#pragma once

#include "IModule.h"
#include "ModuleCapture.h"

class DetectStopSign : public DetectBase
{
public:
  struct Parameters : public IParameters
  {
  public:

  private:
  };

  class Data : public IData
  {
  public:
    void Clear() { _circle.Clear(); }

    Circle GetRegion() { return _circle; }
    void SetRegion(Circle circle) { _circle = circle; }

  private:
    Circle _circle;
  };

  DetectStopSign(IParameters *params, IData *input, IData *output)
  {
    _params = static_cast<Parameters*>(params);
    _input = static_cast<Capture::Data*>(input);
    _output = static_cast<Data*>(output);
  }

  void operator()();
  void PreProcess();
  void Process();

  void Draw();
  void Display();
  void Clear();
 
private:
  Parameters *_params;
  Capture::Data *_input;
  Data *_output;
};