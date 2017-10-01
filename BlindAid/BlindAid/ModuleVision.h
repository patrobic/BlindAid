#pragma once

#include "IModule.h"
#include "IDetector.h"

#include "DetectDepthObstacle.h"
#include "DetectTrafficLight.h"
#include "DetectStopSign.h"

class Vision : public IModule
{
public:
  void Init(std::string path, std::thread *thread, std::mutex *bufferMutex, bool *processingActive, cv::Mat *image, VisionParams *params, VisionResults *results);
  void Start();

private:
  void TVision();

  VisionParams *_params;
  VisionResults *_results;

  std::string _path;
  std::thread *_thread;
  std::mutex *_bufferMutex;
  bool *_processingActive;
  cv::Mat *_image;

  cv::Mat _currentImage;

  DetectStopSign _ssd;
  DetectTrafficLight _tld;
  DetectDepthObstacle _dod;

};