#pragma once

#include "IModule.h"
#include "BaseControl.h"
#include "ModuleVision.h"

class ControlSim : public ControlBase
{
public:
  ControlSim(IParameters *params, IData *input, IData *output) : ControlBase(params, input, output) {}
  void operator()();

private:
  cv::Mat _depthMat;
};