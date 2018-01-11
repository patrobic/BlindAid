#pragma once

#include "IDetect.h"
#include "Capture.h"

namespace Vision
{
  namespace StopSign
  {
    struct Circle
    {
      enum Color { Red, Green, Yellow };
      
      Circle() { Clear(); }

      Circle(cv::Point center, float radius, Color color)
      {
        _center = center;
        _radius = radius;
        _color = color;
        _count = 0;
      }

      void Clear()
      {
        _center = cv::Point(0, 0);
        _radius = 0;
        _color = Red;
        _count = 0;
      }

      float CartesianDistance(Circle &c2) { return (float)cv::norm(_center - c2._center); }
      float RadiusDifference(Circle &c2) { return abs(_radius - c2._radius); }

      cv::Point _center = cv::Point(0, 0);
      float _radius = 0.f;
      Color _color = Red;
      int _count = 0;
    };

    class Data : public IData
    {
    public:
      Data() {}
      void Clear() { _circle.Clear(); }
      bool Valid() { return true; }

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