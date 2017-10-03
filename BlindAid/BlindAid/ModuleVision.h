#pragma once

#include "IModule.h"

#include "DetectDepthObstacle.h"
#include "DetectTrafficLight.h"
#include "DetectStopSign.h"

class Vision : public IModule
{
public:
  void Init(Data *data);
  void operator()();

private:
  void VisionThread();

  DetectStopSign _ssd;
  DetectTrafficLight _tld;
  DetectDepthObstacle _dod;
};