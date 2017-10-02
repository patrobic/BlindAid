#pragma once

#include <atomic>

#include "IModule.h"
#include "IResults.h"

class ControlSim : public IModule
{
public:
  void Init(Data *data, std::thread *thread);
  void Start();

private:
  void TControl();
  void SimulateOutput(int frame);

  Data *_data;
  std::thread *_thread;

  cv::Mat _depthMat;
};