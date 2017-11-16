#pragma once

#include "IParameters.h"
#include "opencv2\core.hpp"

namespace Vision
{
  namespace DepthObstacle
  {
    class Parameters : public SwitchableParameters
    {
    public:
      enum Mode
      {
        FingerRegions,
        HandHunting,
        HeadProtection
      };

      enum Polarity
      {
        CloseIsSmall,
        CloseIsLarge
      };

      Parameters()
      {
        _sbdParams.filterByArea = true;
        _sbdParams.minArea = 20 * 20;
        _sbdParams.maxArea = 120 * 120;
        _sbdParams.filterByCircularity = true;
        _sbdParams.minCircularity = 0.1f;
        _sbdParams.filterByConvexity = true;
        _sbdParams.minConvexity = 0.8f;
        _sbdParams.filterByInertia = true;
        _sbdParams.minInertiaRatio = 0.5f;
        _sbdParams.filterByColor = true;
        _sbdParams.blobColor = 255;
      }

      bool Valid()
      {
        return true;
      }

      Mode GetMode() { return _regionMode; }
      void SetMode(Mode regionMode) { _regionMode = regionMode; }

      Polarity GetIntensityPolarity() { return _intensityPolarity; }
      void SetIntensityPolarity(Polarity intensityPolarity) { _intensityPolarity = intensityPolarity; }

      float GetPercentileToIgnore() { return _percentileToIgnore; }
      void SetPercentileToIgnor(float percentileToIgnore) { _percentileToIgnore = percentileToIgnore; }

      int GetHorzRegions() { return _horzRegions; }
      void SetHorzRegions(int horzRegions) { _horzRegions = horzRegions; }

      int GetVertRegions() { return _vertRegions; }
      void SetVertRegions(int vertRegions) { _vertRegions = vertRegions; }

      float GetCenterRegionHeight() { return _centerRegionHeight; }
      void SetCenterRegionHeight(float centerRegionHeight) { _centerRegionHeight = centerRegionHeight; }

      float GetCenterRegionsWidth() { return _centerRegionsWidth; }
      void SetCenterRegionsWidth(float centerRegionsWidth) { _centerRegionsWidth = centerRegionsWidth; }

      cv::Point GetDefaultHandPosition() { return _defaultHandPosition; }
      void SetDefaultHandPosition(cv::Point defaultHandPosition) { _defaultHandPosition = defaultHandPosition; }

      cv::Scalar GetHandDotHsvRange(int n) { return _handDotHsvRange[n]; }
      void SetHandDotHsvRange(int n, cv::Scalar handDotHsvRange) { _handDotHsvRange[n] = handDotHsvRange; }

      cv::SimpleBlobDetector::Params GetSbdParams() { return _sbdParams; }
      void SetSbdParams(cv::SimpleBlobDetector::Params sbdParams) { _sbdParams = sbdParams; }

    private:
      // mode used in defining region position and sizes.
      Mode _regionMode = Mode::HandHunting;

      // significance of pixel values (i.e. is distance directly or inversely proportional to pixel value).
      Polarity _intensityPolarity = Polarity::CloseIsSmall;

      // percentage of nearest pixels to ignore (to avoid false detections from noise etc.)
      float _percentileToIgnore = 0.01f;

      // number of horizontal regions to split the frame in (default is 3: upper, middle and lower).
      int _horzRegions = HORZ_REGIONS;

      // number of vertical regions to split the frame in (default is 5: one for each finger).
      int _vertRegions = VERT_REGIONS;

      // height of the central region (for hand hunting mode), other regions evenly distributed in remaining height.
      float _centerRegionHeight = 0.4f;

      // width of the central region (for hand hunting mode), other regions evenly distributed in remaining width.
      float _centerRegionsWidth = 0.1f;

      cv::Point _defaultHandPosition = cv::Point(320, 240);

      cv::Scalar _handDotHsvRange[2] = { cv::Scalar(100 / 2, 100, 100), cv::Scalar(140 / 2, 255, 255) };

      cv::SimpleBlobDetector::Params _sbdParams;
    };
  }

  namespace TrafficLight
  {
    namespace BlobDetector
    {
      class Parameters : public IParameters
      {
      public:
        Parameters() { InitBlobParams(); }

        bool Valid()
        {
          return true;
        }

        cv::Scalar GetColorRange(int color, int index) { return _colorRanges[color][index]; }
        void SetColorRange(int color, int index, cv::Scalar scalar) { _colorRanges[color][index] = scalar; }

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

        // HSV color range for red/green/yellow masking.
        cv::Scalar _colorRanges[3][2] = {
          { cv::Scalar(150, 150, 180), cv::Scalar(10, 255, 255) },
          { cv::Scalar(40, 110, 150), cv::Scalar(80, 255, 255) },
          { cv::Scalar(10, 110, 150), cv::Scalar(40, 255, 255) } };

        // parameters class for blobdetector.
        cv::SimpleBlobDetector::Params _blobParams;
      };
    }

    namespace DeepLearning
    {
      class Parameters : public IParameters
      {
      public:
        bool Valid()
        {
          return true;
        }

      private:
        // TODO: deep learning parameters once class is implemented.

      };
    }

    class Parameters : public SwitchableParameters
    {
    public:
      enum Mode
      {
        BlobDetector,
        DeepLearning
      };

      bool Valid()
      {
        return true;
      }

      BlobDetector::Parameters *GetBlobDetectorParams() { return &_blobDetectorParams; }

      DeepLearning::Parameters *GetDeepLearningParams() { return &_deepLearningParams; }

      const Mode &GetMode() const { return _mode; }
      void SetMode(Mode mode) { _mode = mode; }

      float GetUpperRegionToAnalyze() { return _topRegionToAnalyze; }
      void SetLowerRegionToAnalyzer(float topRegionToAnalyzeR) { _topRegionToAnalyze = topRegionToAnalyzeR; }

      int GetConsecutiveCount() { return _consecutiveCount; }
      void SetConsecutiveCount(int consecutiveCount) { _consecutiveCount = consecutiveCount; }

      int GetMaximumDistance() { return _maximumDistance; }
      void SetMaximumDistance(int maximumDistance) { _maximumDistance = maximumDistance; }

      int GetMaximumRadiusDiff() { return _maximumRadiusDiff; }
      void SetMaximumRadiusDiff(int maximumRadiusDiff) { _maximumRadiusDiff = maximumRadiusDiff; }

    private:
      // parameters specific to blob detector mode.
      BlobDetector::Parameters _blobDetectorParams;

      // parameters specific to deep learning mode.
      DeepLearning::Parameters _deepLearningParams;

      // detection mode to use (CV or AI).
      Mode _mode = BlobDetector;

      // upper region to inspect for traffic lights.
      float _topRegionToAnalyze = 0.5f;

      // consecutive detection
      int _consecutiveCount = 4;

      //  maximum distance and radius difference thresholds.
      int _maximumDistance = 25;
      int _maximumRadiusDiff = 5;
    };
  }

  namespace StopSign
  {
    struct Parameters : public SwitchableParameters
    {
    public:
      bool Valid()
      {
        return true;
      }

    private:

    };
  }

  class Parameters : public SwitchableParameters
  {
  public:
    DepthObstacle::Parameters *GetDepthObstacleParams() { return &_dodParams; }
    TrafficLight::Parameters *GetTrafficLightParams() { return &_tldParams; }
    StopSign::Parameters *GetStopSignParams() { return &_ssdParams; }

    bool Valid()
    {
      return true;
    }

  private:
    // parameters class for depth obstacle detector.
    DepthObstacle::Parameters _dodParams;

    // parameters class for traffic light detector.
    TrafficLight::Parameters _tldParams;

    // parameters class for stop sign detector.
    StopSign::Parameters _ssdParams;
  };
}