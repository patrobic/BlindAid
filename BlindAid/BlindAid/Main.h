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
  
  // Simulation (Video Load, Display Control)
  void TestVideo();
  void TestPhoto();
  cv::Mat _image;
  Core _core;

  // OLD: for individual modules.
  VisionParams _params;
  VisionResults _results;

  DetectStopSign _ssd;
  DetectTrafficLight _tld;
  DetectDepthObstacle _dod;

  CaptureSim _captureSim;
  Vision _vision;
  ControlSim _controlSim;
};