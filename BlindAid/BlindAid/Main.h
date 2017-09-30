#pragma once

#include "DepthObstacleDetection.h"
#include "TrafficLightDetector.h"
#include "StopSignDetector.h"
#include "Parameters.h"

class Main
{
public:
  void Start();

private:
  void LoadImage(string path);
  void TestDod();
  void TestTld();
  void TestSsd();

  Parameters _params;
  cv::Mat _image;

};