#include "Core.h"

void Core::InitSimulation(std::string path)
{
  _path = path;

  _captureSim.Init(_path, &_captureThread, &_bufferMutex, &_processingActive, &_image);

  _vision.Init(_path, &_visionThread, &_bufferMutex, &_processingActive, &_image, &_params, &_results);

  _controlSim.Init();
}

void Core::Init()
{
  // initialize hardware capture & control
}

void Core::StartSimulation()
{
  _captureSim.Start();
  _vision.Start();
  _controlSim.Start();

  _captureThread.join();
  _visionThread.join();
  //_controlThread->join();
}
