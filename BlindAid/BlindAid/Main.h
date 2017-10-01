#pragma once

#include "DepthObstacleDetection.h"
#include "TrafficLightDetector.h"
#include "StopSignDetector.h"
#include "opencv2\videoio.hpp"
#include <mutex>
#include <thread>

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
  void TLoadVideo();
  void TProcessFrames();

  Parameters _params;
  cv::Mat _image;
  cv::Mat _currentImage;
  bool _processingActive;
  mutex _bufferMutex;

  cv::VideoCapture _cap;

  StopSignDetector _ssd;
  TrafficLightDetector _tld;
  DepthObstacleDetector _dod;

  TrafficLightResults _tldResults;
  StopSignResults _ssdResults;
  DepthObstacleResults _dodResults;
};