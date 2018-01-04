#pragma once

#include "IDetect.h"
#include "Capture.h"

namespace Vision
{
  namespace TrafficLight
  {
    class Result : public IResult
    {
    public:
      enum Color { None, Red, Green, Yellow };

      Result() { _radius = 0; }
      Result(cv::Point center, float radius, Color color) { _center = center; _radius = radius; _color = color; _count = 1; }
      void Clear() { _center = cv::Point(0, 0); _radius = 0; _color = Red; }

      float CartesianDistance(Result &c2) { return (float)cv::norm(_center - c2._center); }
      float RadiusDifference(Result &c2) { return abs(_radius - c2._radius); }
      bool SameColor(Result &c2) { return _color == c2._color; }

      cv::Point _center;
      float _radius;
      Color _color;
      int _count = 0;
    };

    class Data : public IData
    {
    public:
      void Clear() { _results.clear(); }

      bool Valid()
      {
        return true;
      }

      std::vector<Result> Get() { return FilterByConsecutiveCount(); }
      void Set(std::vector<Result> &results) { MatchPoints(results); }
      void SetSingle(Result::Color color) { if (_results.at(0)._color == color) _results.at(0)._count++; else if (_results.size() == 0) _results.push_back(Result(cv::Point(320, 240), 10, color)); else _results.at(0) = Result(cv::Point(320, 240), 10, color); }
      int Size() { return (int)_results.size(); }
      Result& At(int i) { return _results.at(i); }
      void SetParams(int consecutiveCount, int maximumDistance, int maximumRadiusDiff)
      { _consecutiveCount = consecutiveCount; _maximumDistance = maximumDistance; _maximumRadiusDiff = maximumRadiusDiff; }

      std::vector<Result> FilterByConsecutiveCount();
      void MatchPoints(std::vector<Result> &results);

    private:
      std::vector<Result> _results;

      int _consecutiveCount;
      int _maximumDistance;
      int _maximumRadiusDiff;
    };

    class Base : public IDetect<Parameters, Capture::Data, Data>
    {
    public:
      Base(IParameters *params, IData *input, IData *output);
      static Base *Base::MakeTrafficLight(IParameters *params, IData *input, IData *output);

    protected:

    };
  }
}