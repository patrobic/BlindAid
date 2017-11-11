#pragma once

#include "IModule.h"
#include "ControlBase.h"
#include "Vision.h"

namespace Control
{
  class Simulate : public Base
  {
  public:
    Simulate(IParameters *params, IData *input, IData *output);
    void Process();

  private:
    cv::Mat _depthMat;
  };
}