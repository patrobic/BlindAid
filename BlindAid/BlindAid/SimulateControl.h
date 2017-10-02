#pragma once

#include <atomic>

#include "IModule.h"
#include "IResults.h"

class ControlSim : public IModule
{
public:
  void Init(std::thread *thread, std::mutex *resultMutex, atomic_bool *visionDone, atomic_bool *_newProcessedFrame, VisionResults *results);
  void Start();

private:
  void TControl();
  void SimulateOutput(int frame);

  std::thread *_thread;
  std::mutex *_resultMutex;
  atomic_bool *_visionDone;
  atomic_bool *_newProcessedFrame;

  VisionResults *_results;
  cv::Mat _depthMat;
};