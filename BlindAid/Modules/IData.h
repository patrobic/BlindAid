#pragma once

#include <array>

#include "opencv2\core.hpp"
#include "IParameters.h"

class IData
{
public:
  virtual void Clear() = 0;
  // TODO: check that parameters are valid in all Modules.
  // virtual bool Valid() = 0;

protected:

};

struct Circle
{
  enum Color
  {
    Red,
    Green,
    Yellow
  };

  Circle() { _radius = 0; }
  Circle(cv::Point center, int radius, Color color) { _center = center; _radius = radius; _color = color; }
  void Clear() { _center = cv::Point(0, 0); _radius = 0; _color = Red; }

  cv::Point _center;
  int _radius;
  Color _color;
};

struct Region
{
  Region() {}
  Region(cv::Rect rect, int intensity) { _region = rect; _intensity = intensity; }
  void Clear() { _region = cv::Rect(cv::Point(0,0), cv::Point(0, 0)); _intensity = 0; }

  cv::Rect _region;
  int _intensity;
};