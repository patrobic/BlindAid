#pragma once

#include "IDetect.h"
#include "Capture.h"

struct Circle
{
  enum Color { Red, Green, Yellow };

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

namespace Vision
{
  namespace StopSign
  {
    class Data : public IData
    {
    public:
      void Clear() { _circle.Clear(); }
      bool Valid()
      {
        return true;
      }

      Circle GetRegion() { return _circle; }
      void SetRegion(Circle circle) { _circle = circle; }

    private:
      Circle _circle;
    };

    class Base : public IDetect<Parameters, Capture::Data, Data>
    {
    public:
      Base(IParameters *params, IData *input, IData *output);

    private:
      void Process();
    };
  }
}