#pragma once

#include "DepthObstacleDetection.h"
#include "TrafficLightDetector.h"
#include "StopSignDetector.h"

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

  Parameters _params;
  cv::Mat _image;

  StopSignDetector _ssd;
  TrafficLightDetector _tld;
  DepthObstacleDetector _dod;

  TrafficLightResults _tldResults;
  StopSignResults _ssdResults;
  DepthObstacleResults _dodResults;
};