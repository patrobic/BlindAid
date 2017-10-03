#pragma once

#include "IModule.h"

class Display : public IModule
{
public:
  void Init(Data *data);
  void operator()();

private:
  void DisplayThread();

  void ShowDepthObstacles();
  void ShowTrafficLights();
  void ShowStopSign();

  void DisplayImage();
};