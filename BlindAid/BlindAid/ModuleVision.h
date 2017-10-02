#pragma once

#include <atomic>
#include "IModule.h"
#include "IDetector.h"

#include "DetectDepthObstacle.h"
#include "DetectTrafficLight.h"
#include "DetectStopSign.h"


class Vision : public IModule
{
public:
  void Init(Data *data, std::thread *thread);
  void Start();

private:
  void TVision();
  void DisplayImage(int frame, double time);

  Data *_data;

  std::thread *_thread;

  DetectStopSign _ssd;
  DetectTrafficLight _tld;
  DetectDepthObstacle _dod;

};