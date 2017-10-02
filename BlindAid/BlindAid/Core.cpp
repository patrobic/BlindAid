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
void Core::Simulate(bool isVideo, std::string path)
{
  CaptureSim captureSim;
  ControlSim controlSim;

  _captureDone = false;
  _visionDone = false;

  captureSim.Init(isVideo, path, &_captureThread, &_bufferMutex, &_captureDone, &_newCapturedFrame, &_image);
  _vision.Init(&_visionThread, &_bufferMutex, &_resultMutex, &_captureDone, &_visionDone, &_newCapturedFrame, &_newProcessedFrame, &_image, &_params, &_results);
  controlSim.Init(&_controlThread, &_resultMutex, &_visionDone, &_newProcessedFrame, &_results);

  captureSim.Start();
  _vision.Start();
  controlSim.Start();

  _captureThread.join();

  _visionThread.join();
  _controlThread.join();
}