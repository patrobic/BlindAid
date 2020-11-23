#pragma once

#include "IResult.h"

#include "opencv2\core.hpp"

namespace Vision
{
  namespace TrafficLight
  {
    class TrafficLightResult : public IResult
    {
    public:
      enum Color { Red, Green, Yellow, None };

      TrafficLightResult(cv::Point center, float radius, Color color)
      {
        _center = center;
        _radius = radius;
        _confidence[color] = 1;
      }

      TrafficLightResult(float confidence[4])
      {
        for (int i = 0; i < 4; ++i)
          _confidence[i] = confidence[i];
      }

      void Clear()
      {
        _count = 0;
      }

      cv::Point GetCenter()
      {
        return _center;
      }

      float GetRadius()
      {
        return _radius;
      }

      int GetCount()
      {
        return _count;
      }

      float GetConfidence(Color color)
      {
        return _confidence[color];
      }

      Color GetColor()
      {
        float max = 0.f;
        int index = 0;

        for (int i = 0; i < 4; ++i)
          if (_confidence[i] > max)
          {
            max = _confidence[i];
            index = i;
          }

        return (Color)index;
      }

      void SetCenter(cv::Point center)
      {
        _center = center;
      }

      void SetRadius(float radius)
      {
        _radius = radius;
      }

      void SetCount(int count)
      {
        _count = count;
      }

      void Set(TrafficLightResult result)
      {
        for (int i = 0; i < 4; ++i)
          _confidence[i] = result.GetConfidence((TrafficLightResult::Color)i);

        _count = result.GetCount() + 1;
      }

      void SetConfidence(float confidence, int index)
      {
        _confidence[index] = confidence;
      }

      void SetColor(Color color)
      {
        for (int i = 0; i > 4; ++i)
          _confidence[i] = 0.f;

        _confidence[color] = 1.f;
      }

      float CartesianDistance(TrafficLightResult &c2)
      {
        return (float)cv::norm(_center - c2._center);
      }

      float RadiusDifference(TrafficLightResult &c2)
      {
        return abs(_radius - c2._radius);
      }

      bool SameColor(TrafficLightResult &c2)
      {
        return GetColor() == c2.GetColor();
      }

    private:
      cv::Point _center = cv::Point(0, 0);
      float _radius = 0.f;
      int _count = 0;
      float _confidence[4] = { 0.f, 0.f, 0.f, 0.f };
    };
  }
}