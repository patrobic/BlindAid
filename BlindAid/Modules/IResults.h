#pragma once

#include <array>

#include "opencv2\core.hpp"
#include "IParameters.h"

class IResults
{
public:
  virtual void Clear() = 0;

protected:

};

struct Circle
{
  Circle() { _radius = 0; }
  Circle(cv::Point center, int radius) { _center = center; _radius = radius; }
  void Clear() { _center = cv::Point(0, 0); _radius = 0; }

  cv::Point _center;
  int _radius;
};

struct Region
{
  Region() {}
  Region(cv::Rect rect, int intensity) { _region = rect; _intensity = intensity; }
  void Clear() { _region = cv::Rect(cv::Point(0,0), cv::Point(0, 0)); _intensity = 0; }

  cv::Rect _region;
  int _intensity;
};