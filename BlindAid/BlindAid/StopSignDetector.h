#pragma once

#include<iostream>

#include "Parameters.h"
#include "opencv2\core.hpp"
#include "opencv2\imgcodecs.hpp"
#include "opencv2\highgui.hpp"
#include "opencv2\imgproc.hpp"
#include "opencv2\features2d.hpp"

using namespace std;

struct StopSign
{
  StopSign(cv::Point point, float radius)
  {
    _point = point;
    _radius = radius;
  }

  cv::Point _point;
  int _radius;
};

class StopSignDetector
{
public:
  StopSignDetector(StopSignParams params);
  void DetectStopSign(cv::Mat image);

private:
  StopSignParams _params;
  cv::Mat _rgbImage;

};