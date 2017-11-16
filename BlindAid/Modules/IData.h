#pragma once

#include <array>

#include "opencv2\core.hpp"
#include "IParameters.h"

class IData
{
public:
  virtual bool Valid() = 0;
  virtual void Clear() = 0;

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
  Circle(cv::Point center, float radius, Color color) { _center = center; _radius = radius; _color = color; }
  void Clear() { _center = cv::Point(0, 0); _radius = 0; _color = Red; }

  float CartesianDistance(Circle &c2)
  {
    return (float)cv::norm(_center - c2._center);
  }

  float RadiusDifference(Circle &c2)
  {
    return abs(_radius - c2._radius);
  }

  cv::Point _center;
  float _radius;
  Color _color;
  int _count = 0;
};

struct Region
{
  Region() {}
  Region(cv::Rect rect, int intensity) { _region = rect; _intensity = intensity; }
  void Clear() { _region = cv::Rect(cv::Point(0,0), cv::Point(0, 0)); _intensity = 0; }

  cv::Rect _region;
  int _intensity;
};