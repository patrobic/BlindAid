#pragma once

#include <atomic>

#include "ModuleCapture.h"
#include "ModuleVision.h"
#include "ModuleControl.h"

#include "SimulateCapture.h"
#include "SimulateControl.h"

class Core
{
public:
  bool Init();
  void Start();
  void Simulate(bool isVideo, std::string path);

private:
  cv::Mat _image;
  atomic_bool _captureDone;
  atomic_bool _visionDone;
  atomic_bool _newCapturedFrame;
  atomic_bool _newProcessedFrame;
  std::mutex _bufferMutex;
  std::mutex _resultMutex;

  VisionParams _params;
  VisionResults _results;

  Capture _capture;
  Vision _vision;
  Control _control;

  std::thread _captureThread;
  std::thread _visionThread;
  std::thread _controlThread;
};