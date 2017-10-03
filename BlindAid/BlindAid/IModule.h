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

struct Data
{
  std::thread _captureThread;
  std::thread _visionThread;
  std::thread _controlThread;
  std::thread _displayThread;

  std::mutex _bufferMutex;
  std::mutex _currentBufferMutex;
  std::mutex _resultMutex;

  std::atomic_bool _captureDone;
  std::atomic_bool _visionDone;
  std::atomic_bool _newFrameForVision;
  std::atomic_bool _newFrameForControl;
  std::atomic_bool _newFrameForDisplay;

  cv::Mat _colorImage;
  cv::Mat _depthImage;
  cv::Mat _currentColorImage;
  cv::Mat _currentDepthImage;

  Parameters _params;
  Results _results;
};

class IModule
{
public:
  virtual void Init(Data *data) = 0;
  virtual void operator()() = 0;

protected:
  Data *_data;
};