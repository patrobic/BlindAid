#pragma once

#include "IModule.h"
#include "IResults.h"

class Display
{
public:
  void Init(Data *data, std::thread *thread);
  void Start();

private:
  void DisplayT();

  void ShowDepthObstacles();
  void ShowTrafficLights();
  void ShowStopSign();

  Data *_data;
  std::thread *_thread;
};