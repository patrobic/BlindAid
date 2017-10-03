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

class IDetector
{
public:
  virtual void Init(Parameters *params, const cv::Mat *image, Results *results) = 0;
  virtual void operator()() = 0;
  virtual void PreProcess() = 0;
  virtual void Process() = 0;

  virtual void Draw() = 0;
  virtual void Display() = 0;
  virtual void Clear() = 0;

protected:
  const cv::Mat *_colorImage;
  const cv::Mat *_depthImage;

};