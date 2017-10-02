#pragma once

#include <atomic>

#include "ModuleCapture.h"
#include "ModuleVision.h"
#include "ModuleControl.h"
#include "ModuleDisplay.h"

#include "SimulateCapture.h"
#include "SimulateControl.h"

class Core
{
public:
  bool Init();
  void Start();
  void Simulate(bool isVideo, std::string colorPath, std::string depthPath);

private:
  Data _data;

  Capture _capture;
  Vision _vision;
  Control _control;
  Display _display;

  std::thread _captureThread;
  std::thread _visionThread;
  std::thread _controlThread;
  std::thread _displayThread;
};