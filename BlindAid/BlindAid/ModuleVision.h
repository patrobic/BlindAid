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
  void Init(std::thread *thread, std::mutex *bufferMutex, std::mutex *resultMutex, atomic_bool *captureDone, atomic_bool *visionDone, atomic_bool *newCapturedFrame, atomic_bool *newProcessedFrame, cv::Mat *image, VisionParams *params, VisionResults *results);
  void Start();

private:
  void TVision();
  void DisplayImage(int frame, double time);

  VisionParams *_params;
  VisionResults *_results;

  std::thread *_thread;
  std::mutex *_bufferMutex;
  std::mutex *_resultMutex;
  atomic_bool *_captureDone;
  atomic_bool *_visionDone;
  atomic_bool *_newCapturedFrame;
  atomic_bool *_newProcessedFrame;
  cv::Mat *_image;

  cv::Mat _currentImage;

  DetectStopSign _ssd;
  DetectTrafficLight _tld;
  DetectDepthObstacle _dod;

};