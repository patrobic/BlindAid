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

  class Results : public IResults
  {
  public:
    void Clear() { _circle.Clear(); }

    Circle GetRegion() { return _circle; }
    void SetRegion(Circle circle) { _circle = circle; }

  private:
    Circle _circle;
  };

  DetectStopSign(Data *data, IParameters *params, IResults *input, IResults *output)
  {
    _data = data;
    _params = static_cast<Parameters*>(params);
    _input = static_cast<Capture::Results*>(input);
    _output = static_cast<Results*>(output);
  }

  void operator()();
  void PreProcess();
  void Process();

  void Draw();
  void Display();
  void Clear();
 
private:
  Parameters *_params;
  Capture::Results *_input;
  Results *_output;
};