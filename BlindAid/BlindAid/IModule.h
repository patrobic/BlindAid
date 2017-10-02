#pragma once

#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <atomic>

#include "opencv2\core.hpp"
#include "opencv2\imgcodecs.hpp"
#include "opencv2\highgui.hpp"
#include "opencv2\imgproc.hpp"
#include "opencv2\features2d.hpp"

#include "IParameters.h"
#include "IResults.h"

using namespace std;
using namespace std::chrono;

struct Data
{
  std::mutex _bufferMutex;
  std::mutex _resultMutex;

  atomic_bool _captureDone;
  atomic_bool _visionDone;
  atomic_bool _newCapturedFrame;
  atomic_bool _newProcessedFrame;

  cv::Mat _colorImage;
  cv::Mat _depthImage;
  cv::Mat _currentColorImage;
  cv::Mat _currentDepthImage;

  VisionParams _params;
  VisionResults _results;
};

class IModule
{
public:
  //virtual void Init() = 0;
  virtual void Start() = 0;

private:

};