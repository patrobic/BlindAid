#pragma once

#include "DetectBase.h"
#include "CaptureBase.h"

namespace Vision
{
  namespace TrafficLight
  {
    class Parameters : public SwitchableParameters
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
        { cv::Scalar(40, 110, 150), cv::Scalar(80, 255, 255) },
        { cv::Scalar(10, 110, 150), cv::Scalar(40, 255, 255) } };

      // consecutive detection
      int _consecutiveCount = 4;

      //  maximum distance and radius difference thresholds.
      int _maximumDistance = 25;
      int _maximumRadiusDiff = 5;
      
      // parameters class for blobdetector.
      cv::SimpleBlobDetector::Params _blobParams;
    };

    class Result : public IResult
    {
    public:
      enum Color { Red, Green, Yellow };

      Result() { _radius = 0; }
      Result(cv::Point center, int radius, Color color) { _center = center; _radius = radius; _color = color; _count = 1; }
      void Clear() { _center = cv::Point(0, 0); _radius = 0; _color = Red; }

      float CartesianDistance(Result &c2) { return cv::norm(_center - c2._center); }
      float RadiusDifference(Result &c2) { return abs(_radius - c2._radius); }
      bool SameColor(Result &c2) { return _color == c2._color; }

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

      std::vector<Result> FilterByConsecutiveCount();
      void MatchPoints(std::vector<Result> &results);

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