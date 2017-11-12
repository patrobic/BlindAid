#pragma once

#include "DetectBase.h"
#include "CaptureBase.h"

namespace Vision
{
  namespace TrafficLight
  {
    class Parameters : public IParameters
    {
    public:
      enum Mode
      {
        BlobDetector,
        DeepLearning
      };

      Parameters() { InitBlobParams(); }

      bool Valid()
      {
        return true;
      }

      const Mode &GetMode() const { return _mode; }
      void SetMode(Mode mode) { _mode = mode; }

      float GetUpperRegionToAnalyze() { return _topRegionToAnalyze; }
      void SetLowerRegionToAnalyzer(float topRegionToAnalyzeR) { _topRegionToAnalyze = topRegionToAnalyzeR; }

      cv::Scalar GetColorRange(int color, int index) { return _colorRanges[color][index]; }
      void SetColorRange(int color, int index, cv::Scalar scalar) { _colorRanges[color][index] = scalar; }

      int GetConsecutiveCount() { return _consecutiveCount; }
      void SetConsecutiveCount(float consecutiveCount) { _consecutiveCount = consecutiveCount; }

      int GetMaximumDistance() { return _maximumDistance; }
      void SetMaximumDistance(float maximumDistance) { _maximumDistance = maximumDistance; }

      int GetMaximumRadiusDiff() { return _maximumRadiusDiff; }
      void SetMaximumRadiusDiff(float maximumRadiusDiff) { _maximumRadiusDiff = maximumRadiusDiff; }

      cv::SimpleBlobDetector::Params *GetBlobParams() { return &_blobParams; }

    private:
      void InitBlobParams()
      {
        _blobParams.filterByArea = true;
        _blobParams.minArea = 4 * 4;
        _blobParams.maxArea = 60 * 60;
        _blobParams.filterByCircularity = true;
        _blobParams.minCircularity = 0.1f;
        _blobParams.filterByConvexity = true;
        _blobParams.minConvexity = 0.8f;
        _blobParams.filterByInertia = true;
        _blobParams.minInertiaRatio = 0.5f;
        _blobParams.filterByColor = true;
        _blobParams.blobColor = 255;
      }

      // detection mode to use (CV or AI).
      Mode _mode = BlobDetector;

      // upper region to inspect for traffic lights.
      float _topRegionToAnalyze = 0.5f;

      // HSV color range for red/green/yellow masking.
      cv::Scalar _colorRanges[3][2] = {
        { cv::Scalar(150, 150, 180), cv::Scalar(10, 255, 255) },
        { cv::Scalar(40, 150, 180), cv::Scalar(80, 255, 255) },
        { cv::Scalar(10, 110, 160), cv::Scalar(40, 255, 255) } };

      // consecutive detection
      int _consecutiveCount = 3;

      //  maximum distance and radius difference thresholds.
      int _maximumDistance = 25;
      int _maximumRadiusDiff = 7;
      
      // parameters class for blobdetector.
      cv::SimpleBlobDetector::Params _blobParams;
    };

    class Result //: public IResult
    {
    public:
      enum Color
      {
        Red,
        Green,
        Yellow
      };

      Result() { _radius = 0; }
      Result(cv::Point center, int radius, Color color) { _center = center; _radius = radius; _color = color; _count = 1; }
      void Clear() { _center = cv::Point(0, 0); _radius = 0; _color = Red; }

      float CartesianDistance(Result &c2)
      {
        return cv::norm(_center - c2._center);
      }

      float RadiusDifference(Result &c2)
      {
        return abs(_radius - c2._radius);
      }

      bool SameColor(Result &c2)
      {
        return _color == c2._color;
      }

      cv::Point _center;
      int _radius;
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
      int Size() { return (int)_results.size(); }
      Result& At(int i) { return _results.at(i); }
      void SetParams(int consecutiveCount, int maximumDistance, int maximumRadiusDiff)
      { _consecutiveCount = consecutiveCount; _maximumDistance = maximumDistance; _maximumRadiusDiff = maximumRadiusDiff; }

      std::vector<Result> FilterByConsecutiveCount()
      {
        std::vector<Result> filtered;

        for (int i = 0; i < _results.size(); ++i)
        {
          if (_results.at(i)._count > _consecutiveCount)
            filtered.push_back(_results.at(i));
        }

        return filtered;
      }

      // TODO: Must be unit tested thoroughly.
      void MatchPoints(std::vector<Result> &results)
      {
        std::vector<Result> matched; // stores new detections that match previous ones in position and size.
        
        double distance;
        double radiusDifference;
        bool sameColor;
        double minimumDistance = INT_MAX;
        double minimumRadiusDifference;
        bool minimumSameColor;
        int nearestCurrent;
        int nearestPrevious;
        bool found = false;

        // for each point in incoming vector, while remaining points that are close enough still exist.
        do
        {
          minimumDistance = INT_MAX;
          found = false;

          // find nearest pair of current and previous points.
          for (int i = 0; i < results.size(); ++i)
            for (int j = 0; j < _results.size(); ++j)
            {
              distance = results.at(i).CartesianDistance(_results.at(j));
              radiusDifference = results.at(i).RadiusDifference(_results.at(j));
              sameColor = results.at(i).SameColor(_results.at(j));

              // consider two points a pair candidate if distanace and radius thresholds are met, only if it is the closest pair found yet.
              if (distance < minimumDistance && radiusDifference < _maximumRadiusDiff && sameColor)
              {
                minimumDistance = distance;
                minimumRadiusDifference = results.at(i).RadiusDifference(_results.at(j));
                minimumSameColor = true;
                nearestCurrent = i;
                nearestPrevious = j;
                found = true;
              }
            }

          // circle qualifies as existing if its distance to nearest circle is close and radius is similar.
          if (minimumDistance < _maximumDistance && minimumRadiusDifference < _maximumRadiusDiff && minimumSameColor)
          {
            results.at(nearestCurrent)._count = ++_results.at(nearestPrevious)._count; // retreive and increment count from matched point
            matched.push_back(results.at(nearestCurrent)); // insert matched point into temporary vector
            results.erase(results.begin() + nearestCurrent); // remove matched point from incoming vector
            _results.erase(_results.begin() + nearestPrevious); // remove matched point from previous vector also
          }
          else if(found == true)
            results.erase(results.begin() + nearestCurrent);
        } while (minimumDistance < _maximumDistance);

        _results = matched; // store points that were matched with detections from previous frame.
        _results.insert(_results.end(), results.begin(), results.end()); // also store points that were newly detected this frame.
      }

    private:
      std::vector<Result> _results;

      int _consecutiveCount;
      int _maximumDistance;
      int _maximumRadiusDiff;
    };

    class Base : public DetectBase<Parameters, Capture::Data, Data>
    {
    public:
      static Base *Base::MakeTrafficLight(IParameters *params, IData *input, IData *output);
      Base(IParameters *params, IData *input, IData *output);

    protected:

    };
  }
}