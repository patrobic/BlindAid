#pragma once

#include "IParameters.h"
#include "opencv2\core.hpp"

namespace Vision
{
  namespace DepthObstacle
  {
    namespace FixedRegions
    {
      class Parameters : public IParameters
      {
      public:
        Parameters(GlobalParameters *params) : IParameters(params)
        {
          Defaults();
        }

        void Defaults()
        {

        }

        bool Valid()
        {
          return true;
        }

      private:

      };
    }

    namespace HandPosition
    {
      class Parameters : public IParameters
      {
      public:
        Parameters(GlobalParameters *params) : IParameters(params)
        {
          Defaults();
        }

        void Defaults()
        {
          _handDotHsvRange[0] = cv::Scalar(100 / 2, 100, 100);
          _handDotHsvRange[1] = cv::Scalar(140 / 2, 255, 255);

          _handDetectorParams.filterByArea = true;
          _handDetectorParams.minArea = 20 * 20;
          _handDetectorParams.maxArea = 120 * 120;
          _handDetectorParams.filterByCircularity = true;
          _handDetectorParams.minCircularity = 0.1f;
          _handDetectorParams.filterByConvexity = true;
          _handDetectorParams.minConvexity = 0.8f;
          _handDetectorParams.filterByInertia = true;
          _handDetectorParams.minInertiaRatio = 0.5f;
          _handDetectorParams.filterByColor = true;
          _handDetectorParams.blobColor = 255;
        }

        bool Valid()
        {
          return true;
        }

        cv::Scalar GetHandDotHsvRange(int n) { return _handDotHsvRange[n]; }
        void SetHandDotHsvRange(int n, cv::Scalar handDotHsvRange) { _handDotHsvRange[n] = handDotHsvRange; }

        cv::SimpleBlobDetector::Params GetHandDetectorParams() { return _handDetectorParams; }
        void SetHandDetectorParams(cv::SimpleBlobDetector::Params handDetectorParams) { _handDetectorParams = handDetectorParams; }

      private:

        // color range of dot on hand indicating its position.
        cv::Scalar _handDotHsvRange[2];

        // OpenCV blob detector params for finding do on hand.
        cv::SimpleBlobDetector::Params _handDetectorParams;
      };
    }

    class Parameters : public SwitchableParameters
    {
    public:
      enum Version { FixedRegions, HandPosition, Reduced };
      enum Polarity { CloseIsSmall, CloseIsLarge };

      Parameters(GlobalParameters *params) : SwitchableParameters(params), _fixedRegionsParams(params), _handPositionParams(params)
      {
        Defaults();
      }

      void Defaults()
      {
        _version = Version::FixedRegions;

        _consecutiveCount = 3;
        _frameConsecutiveCount = 2;

        _horizontalRegions = HORZ_REGIONS;
        _verticalRegions = VERT_REGIONS;
        _regionHeight = 0.4f;
        _regionWidth = 0.2f;
        _horizontalCoverage = 0.75f;
        _verticalCoverage = 1.f;
        _snapToEdges = true;
        _defaultCenter = cv::Point(320, 240);

        _minimumDistance = 640;
        _maximumDistance = 5000;
        _percentileToIgnore = 0.06f;
        _intensityPolarity = Polarity::CloseIsSmall;
        _histogramBins = 256;

        float bounds[HORZ_REGIONS][VERT_REGIONS] = {
          { 1000, 1100, 1200, 1100, 1000 },
          { 1100, 1200, 1300, 1200, 1100 },
          { 1000, 1100, 1200, 1100, 1000 } };

        for (int i = 0; i < HORZ_REGIONS; ++i)
          for (int j = 0; j < VERT_REGIONS; ++j)
            _farthestBound[i][j] = bounds[i][j];

        _minimumVibration = 25.f;
        _maximumVibration = 192.f;
        _validRatioThreshold = 0.1f;
        _nearestObstacleOnly = true;
        _lessThanMaxToIgnore = 0.1f;
      }

      bool Valid()
      {
        return true;
      }

      FixedRegions::Parameters *GetFixedRegionsParams() { return &_fixedRegionsParams; }

      HandPosition::Parameters *GetHandPositionParams() { return &_handPositionParams; }

      int GetHorizontalRegions() { return _horizontalRegions; }
      void SetHorizontalRegions(int horzRegions) { _horizontalRegions = horzRegions; }

      int GetVerticalRegions() { return _verticalRegions; }
      void SetVerticalRegions(int vertRegions) { _verticalRegions = vertRegions; }

      Version GetVersion() { return _version; }
      void SetVersion(Version mode) { _version = mode; }

      int GetConsecutiveCount() { return _consecutiveCount; }
      void SetConsecutiveCount(int consecutiveCount) { _consecutiveCount = consecutiveCount; }

      int GetFrameConsecutiveCount() { return _frameConsecutiveCount; }
      void SetFrameConsecutiveCount(int consecutiveCount) { _frameConsecutiveCount = consecutiveCount; }

      float GetRegionHeight() { return _regionHeight; }
      void SetRegionHeight(float centerRegionHeight) { _regionHeight = centerRegionHeight; }

      float GetRegionWidth() { return _regionWidth; }
      void SetRegionWidth(float centerRegionsWidth) { _regionWidth = centerRegionsWidth; }

      float GetHorizontalCoverage() { return _horizontalCoverage; }
      void SetHorizontalCoverage(float horizontalCoverage) { _horizontalCoverage = horizontalCoverage; }

      float GetVerticalCoverage() { return _verticalCoverage; }
      void SetVerticalCoverage(float verticalCoverage) { _verticalCoverage = verticalCoverage; }

      bool GetSnapToEdges() { return _snapToEdges; }
      void SetSnapToEdges(bool snapToEdges) { _snapToEdges = snapToEdges; }

      cv::Point GetDefaultCenter() { return _defaultCenter; }
      void SetDefaultCenter(cv::Point defaultCenter) { _defaultCenter = defaultCenter; }

      float GetMinimumDistance() { return _minimumDistance; }
      void SetMinimumDistance(float minDistance) { _minimumDistance = minDistance; }

      float GetMaximumDistance() { return _maximumDistance; }
      void SetMaximumDistance(float maxDistance) { _maximumDistance = maxDistance; }

      float GetPercentileToIgnore() { return _percentileToIgnore; }
      void SetPercentileToIgnore(float percentileToIgnore) { _percentileToIgnore = percentileToIgnore; }

      Polarity GetIntensityPolarity() { return _intensityPolarity; }
      void SetIntensityPolarity(Polarity intensityPolarity) { _intensityPolarity = intensityPolarity; }

      int GetHistogramBins() { return _histogramBins; }
      void SetHistogramBins(int histogramBins) { _histogramBins = histogramBins; }

      float GetFarthestBound(int finger, int level) { return _farthestBound[level][finger]; }
      void SetFarthestBound(int finger, int level, float farthestBound) { _farthestBound[level][finger] = farthestBound; }

      float GetMinimumVibration() { return _minimumVibration; }
      void SetMinimumVibration(float minimumVibration) { _minimumVibration = minimumVibration; }

      float GetMaximumVibration() { return _maximumVibration; }
      void SetMaximumVibration(float maximumVibration) { _maximumVibration = maximumVibration; }

      float GetValidRatioThreshold() { return _validRatioThreshold; }
      void SetValidRatioThreshold(float validRatioThreshold) { _validRatioThreshold = validRatioThreshold; }

      bool GetNearestObstacleOnly() { return _nearestObstacleOnly; }
      void SetNearestObstacleOnly(bool nearestObstacleOnly) { _nearestObstacleOnly = nearestObstacleOnly; }

      float GetLessThanMaxToIgnore() { return _lessThanMaxToIgnore; }
      void SetLessThanMaxToIgnore(float lessThanMaxToIgnore) { _lessThanMaxToIgnore = lessThanMaxToIgnore; }

    private:
      // parameters specific to blob detector mode.
      FixedRegions::Parameters _fixedRegionsParams;

      // parameters specific to deep learning mode.
      HandPosition::Parameters _handPositionParams;

      // number of horizontal regions to split the frame in (default is 3: upper, middle and lower).
      int _horizontalRegions;

      // number of vertical regions to split the frame in (default is 5: one for each finger).
      int _verticalRegions;

      // mode used in defining region position and sizes.
      Version _version;

      // number of frames for which the farthest object will be chosen.
      int _consecutiveCount;

      int _frameConsecutiveCount;

      // height of the central region (for hand hunting mode), other regions evenly distributed in remaining height.
      float _regionHeight;

      // width of the central region (for hand hunting mode), other regions evenly distributed in remaining width.
      float _regionWidth;

      // percentage of frame to analyze horizontally (reduce for head protection mode).
      float _horizontalCoverage;

      // percentage of frame to analyze vertically (reduce for head protection mode).
      float _verticalCoverage;

      // choose whether outer regions will expand to stick to edges.
      bool _snapToEdges;

      // point at which the search regions are centered.
      cv::Point _defaultCenter;

      // minimum object distance supported by camera.
      float _minimumDistance;

      // maximum object distance supported by camera.
      float _maximumDistance;

      // percentage of nearest pixels to ignore (to avoid false detections from noise etc.)
      float _percentileToIgnore;

      // significance of pixel values (i.e. is distance directly or inversely proportional to pixel value).
      Polarity _intensityPolarity;

      // number of bins used in histogram calculation.
      int _histogramBins;

      // farthest and nearest distance range (in meters) to consider in depth detection (zero to disable region).
      float _farthestBound[HORZ_REGIONS][VERT_REGIONS];
      float _nearestBound;

      // minimum and maximum vibration instensity ratios at farthest and nearest distances.
      float _minimumVibration;
      float _maximumVibration;

      // camera maximum depth distance (in meters), i.e. distance at pixel = 255.
      float _maximumDepthSpec;

      // minimum ratio of non-zero pixels for successful detection.
      float _validRatioThreshold;

      // vibrate the finger of the region with the nearest detection only.
      bool _nearestObstacleOnly;

      // vibration threshold below which non-nearest objects will be ignored.
      float _lessThanMaxToIgnore;
    };
  }
}