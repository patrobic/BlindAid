#pragma once

#include "IModule.h"
#include "CaptureBase.h"

namespace Capture
{
  class Simulate : public Base
  {
  public:
    Simulate(IParameters *params, IData *input, IData *output);

  private:
    void Process();
    void LoadVideo();
    void LoadPhoto();

    cv::VideoCapture _cap;

    int _frame = 0;
  };
}