#pragma once

#include<iostream>
#include<string>

#include "Parameters.h"

#include "opencv2\core.hpp"
#include "opencv2\imgcodecs.hpp"
#include "opencv2\highgui.hpp"
#include "opencv2\imgproc.hpp"
#include "opencv2\features2d.hpp"

using namespace std;

class IDetectorResults
{
public:


protected:

};

class IDetector
{
public:
  virtual void Init(const IDetectorParams *params, const cv::Mat *image, IDetectorResults *results) = 0;
  virtual void Start() = 0;
  virtual void PreProcess() = 0;
  virtual void Process() = 0;

  virtual void Draw() = 0;
  virtual void Display() = 0;
  virtual void Clear() = 0;

protected:
  const IDetectorParams *_params;
  IDetectorResults *_results;
  const cv::Mat *_image;
};