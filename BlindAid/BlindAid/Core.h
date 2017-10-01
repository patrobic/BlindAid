#pragma once

#include "ModuleCapture.h"
#include "ModuleVision.h"
#include "ModuleControl.h"

#include "SimulateCapture.h"
#include "SimulateControl.h"

class Core
{
public:
  void InitSimulation(std::string path);
  void Init();
  void StartSimulation();

private:
  std::string _path;
  cv::Mat _image;
  bool _processingActive;
  std::mutex _bufferMutex;

  VisionParams _params;
  VisionResults _results;

  Capture _capture;
  Vision _vision;
  Control _control;

  CaptureSim _captureSim;
  ControlSim _controlSim;

  std::thread _captureThread;
  std::thread _visionThread;
  std::thread _controlThread;
};