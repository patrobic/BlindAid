#pragma once

#include "opencv2\core.hpp"

namespace Vision
{
  namespace TrafficLight
  {
    class Result : public IResult
    {
    public:
      enum Color { Red, Green, Yellow, None };

      Result(cv::Point center, float radius, Color color)
      {
        _center = center;
        _radius = radius;
        _count = 1;
      }

      Result(float confidence[4])
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

      void Set(Result result)
      {
        for (int i = 0; i > 4; ++i)
          _confidence[i] = result.GetConfidence((Result::Color)i);

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

      float CartesianDistance(Result &c2)
      {
        return (float)cv::norm(_center - c2._center);
      }

      float RadiusDifference(Result &c2)
      {
        return abs(_radius - c2._radius);
      }

      bool SameColor(Result &c2)
      {
        return GetColor() == c2.GetColor();
      }

    private:
      cv::Point _center;
      float _radius;
      int _count = 0;
      float _confidence[4];
    };

    class Data : public IData
    {
    public:
      Data(Parameters *params)
      {
        _consecutiveCount = params->GetConsecutiveCount();
        _maximumDistance = params->GetMaximumDistance();
        _maximumRadiusDiff = params->GetMaximumRadiusDiff();
      }

      void Clear()
      {
        _results.clear();
      }

      bool Valid()
      {
        return true;
      }

      std::vector<Result> *GetAll()
      {
        return &_results;
      }

      std::vector<Result> Get()
      {
        return FilterByConsecutiveCount();
      }

      Result::Color GetColor()
      {
        _temp.clear();
        _temp = FilterByConsecutiveCount();

        // if more than 1 light exists, it will prioritize return value in enum order (Red, Green, Yellow, None).
        for (int j = 0; j < 4; ++j)
          for (int i = 0; i < _temp.size(); ++i)
            if (_temp[i].GetColor() == j)
              return (Result::Color)j;

        return Result::Color::None;
      }

      void Set(Result result)
      {
        if (result.GetCenter() == cv::Point(0, 0))
          _results[0].Set(result);
        else
          _unfiltered.push_back(result);
      }

      void MatchPoints()
      {
        _temp.clear(); // stores new detections that match previous ones in position and size.

        double distance;
        double radiusDifference;
        bool sameColor;
        double minimumDistance = INT_MAX;
        double minimumRadiusDifference;
        int nearestCurrent;
        int nearestPrevious;
        bool found = false;

        // for each point in incoming vector, while remaining points that are close enough still exist.
        do
        {
          minimumDistance = INT_MAX;
          found = false;

          // find nearest pair of current and previous points.
          for (int i = 0; i < _unfiltered.size(); ++i)
            for (int j = 0; j < _results.size(); ++j)
            {
              distance = _unfiltered.at(i).CartesianDistance(_results.at(j));
              radiusDifference = _unfiltered.at(i).RadiusDifference(_results.at(j));
              sameColor = _unfiltered.at(i).SameColor(_results.at(j));

              // consider two points a pair candidate if distanace and radius thresholds are met, only if it is the closest pair found yet.
              if (distance < minimumDistance && radiusDifference < _maximumRadiusDiff && sameColor)
              {
                minimumDistance = distance;
                minimumRadiusDifference = _unfiltered.at(i).RadiusDifference(_results.at(j));
                nearestCurrent = i;
                nearestPrevious = j;
                found = true;
              }
            }

          // circle qualifies as existing if its distance to nearest circle is close and radius is similar.
          if (minimumDistance < _maximumDistance && minimumRadiusDifference < _maximumRadiusDiff)
          {
            _unfiltered.at(nearestCurrent).SetCount(_results.at(nearestPrevious).GetCount() + 1); // retreive and increment count from matched point
            _temp.push_back(_unfiltered.at(nearestCurrent)); // insert matched point into temporary vector
            _unfiltered.erase(_unfiltered.begin() + nearestCurrent); // remove matched point from incoming vector
            _results.erase(_results.begin() + nearestPrevious); // remove matched point from previous vector also
          }
          else if (found == true)
            _unfiltered.erase(_unfiltered.begin() + nearestCurrent);
        } while (minimumDistance < _maximumDistance);

        _results = _temp; // store points that were matched with detections from previous frame.
        _results.insert(_results.end(), _unfiltered.begin(), _unfiltered.end()); // also store points that were newly detected this frame.

        _unfiltered.clear();
      }

    private:
      std::vector<Result> FilterByConsecutiveCount()
      {
        _temp.clear();

        for (int i = 0; i < _results.size(); ++i)
        {
          if (_results.at(i).GetCount() > _consecutiveCount)
            _temp.push_back(_results.at(i));
        }

        return _temp;
      }

      std::vector<Result> _results;
      std::vector<Result> _unfiltered;
      std::vector<Result> _temp;

      int _consecutiveCount;
      int _maximumDistance;
      int _maximumRadiusDiff;
    };
  }
}