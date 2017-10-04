#pragma once

#include "IModule.h"
#include "ModuleControl.h"
#include "ModuleVision.h"

class ControlSim : public ControlBase
{
public:
  void Init(Data *data, IParameters *params, IResults *input, IResults *output);
  void operator()();

private:
  void ControlThread();
  void SimulateOutput(int frame);

  cv::Mat _depthMat;
};