#pragma once

#include "IModule.h"
#include "ModuleControl.h"
#include "ModuleVision.h"

class ControlSim : public ControlBase
{
public:
  ControlSim(Data *data, IParameters *params, IResults *input, IResults *output) : ControlBase(data, params, input, output) {}
  void operator()();

private:
  cv::Mat _depthMat;
};