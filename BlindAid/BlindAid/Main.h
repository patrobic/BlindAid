#pragma once

#include <mutex>
#include <thread>

#include "opencv2\videoio.hpp"

#include "IDetector.h"
#include "Core.h"

class Main
{
public:
  void Init();
  void Start();
 
private:
  void LoadImage(string path);
  void TestDod();
  void TestTld();
  void TestSsd();
  void TestVideo();

  VisionParams _params;
  VisionResults _results;

  cv::Mat _image;
  bool _processingActive;
  mutex _bufferMutex;

  Core _core;

  // OLD: for individual modules.
  DetectStopSign _ssd;
  DetectTrafficLight _tld;
  DetectDepthObstacle _dod;

  CaptureSim _captureSim;
  Vision _vision;
  ControlSim _controlSim;
};