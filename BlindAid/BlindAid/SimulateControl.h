#pragma once

#include "IModule.h"

class ControlSim : public IModule
{
public:
  void Init(Data *data);
  void operator()();

private:
  void ControlThread();
  void SimulateOutput(int frame);

  cv::Mat _depthMat;
};