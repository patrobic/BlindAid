#include "Core.h"

bool Core::Init()
{
  // TODO: Initialize hardware capture & control.

  return true;
}

void Core::Start()
{

}

// Initialize and start capture & control simulation (does not use any extra memory unless called).
void Core::Simulate(bool isVideo, std::string colorPath, std::string depthPath)
{
  CaptureSim captureSim;
  ControlSim controlSim;

  _data._captureDone = false;
  _data._visionDone = false;

  captureSim.Init(&_data, &_captureThread);
  captureSim.SetPath(isVideo, colorPath, depthPath);
  _vision.Init(&_data, &_visionThread);
  controlSim.Init(&_data, &_controlThread);
  _display.Init(&_data, &_displayThread);

  captureSim.Start();
  _vision.Start();
  controlSim.Start();

  _captureThread.join();

  _visionThread.join();
  _controlThread.join();

  // TODO: display thread not yet in pipeline.
  _display.Start();
}