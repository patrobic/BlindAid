#pragma once

#include "IParameters.h"
#include "opencv2\core.hpp"

namespace Vision
{
  namespace TrafficLight
  {
    namespace BlobDetector
    {
      class BlobDetectorParameters : public IParameters
      {
      public:
        BlobDetectorParameters(GlobalParameters *params) : IParameters(params)
        {
          Defaults();
        }

        void Defaults()
        {
          _colorRanges[0][0] = cv::Scalar(150, 150, 180);
          _colorRanges[0][1] = cv::Scalar(10, 255, 255);
          _colorRanges[1][0] = cv::Scalar(40, 110, 150);
          _colorRanges[1][1] = cv::Scalar(80, 255, 255);
          _colorRanges[2][0] = cv::Scalar(10, 90, 150);
          _colorRanges[2][1] = cv::Scalar(40, 255, 255);

          _blobParams.filterByArea = true;
          _blobParams.minArea = 10 * 10;
          _blobParams.maxArea = 150 * 150;
          _blobParams.filterByCircularity = true;
          _blobParams.minCircularity = 0.1f;
          _blobParams.filterByConvexity = true;
          _blobParams.minConvexity = 0.8f;
          _blobParams.filterByInertia = true;
          _blobParams.minInertiaRatio = 0.5f;
          _blobParams.filterByColor = true;
          _blobParams.blobColor = 255;
        }

        bool Valid()
        {
          return true;
        }

        cv::Scalar GetColorRange(int color, int index) { return _colorRanges[color][index]; }
        void SetColorRange(int color, int index, cv::Scalar scalar) { _colorRanges[color][index] = scalar; }

        cv::SimpleBlobDetector::Params *GetBlobParams() { return &_blobParams; }

      private:
        // HSV color range for red/green/yellow masking.
        cv::Scalar _colorRanges[3][2];

        // parameters class for blobdetector.
        cv::SimpleBlobDetector::Params _blobParams;
      };
    }

    namespace DeepLearning
    {
      class DeepLearningParameters : public IParameters
      {
      public:
        DeepLearningParameters(GlobalParameters *params) : IParameters(params)
        {
          Defaults();
        }

        void Defaults()
        {
          _colorImageSize = cv::Size(224, 224);
          _confidenceThreshold = 0.75f;
        }

        bool Valid()
        {
          return true;
        }

        cv::Size GetColorImageSize() { return _colorImageSize; }
        void SetColorImageSize(cv::Size colorImageSize) { _colorImageSize = colorImageSize; }

        float GetConfidenceThreshold() { return _confidenceThreshold; }
        void SetConfidenceThreshold(float confidenceThreshold) { _confidenceThreshold = confidenceThreshold; }

      private:
        // size of the image sent to the deep learning model.
        cv::Size _colorImageSize;

        // minimum confidence required for a color other than none to be detected.
        float _confidenceThreshold;
      };
    }

    class TrafficLightParameters : public SwitchableParameters
    {
    public:
      enum Version { BlobDetector, DeepLearning };

      TrafficLightParameters(GlobalParameters *params) : SwitchableParameters(params), _blobDetectorParams(params), _deepLearningParams(params)
      {
        Defaults();
      }

      void Defaults()
      {
        _blobDetectorParams.Defaults();
        _deepLearningParams.Defaults();

        _version = DeepLearning;
        _upperRegionRatio = 1.f;
        _centerRegionRatio = 0.75f;
        _consecutiveCount = 3;
        _maximumDistance = 25;
        _maximumRadiusDiff = 5;
      }

      bool Valid()
      {
        return true;
      }

      BlobDetector::BlobDetectorParameters *GetBlobDetectorParams() { return &_blobDetectorParams; }

      DeepLearning::DeepLearningParameters *GetDeepLearningParams() { return &_deepLearningParams; }

      const Version GetVersion() const { return _version; }
      void SetVersion(Version mode) { _version = mode; }

      float GetUpperRegionRatio() { return _upperRegionRatio; }
      void SetUpperRegionRatio(float upperRegionRatio) { _upperRegionRatio = upperRegionRatio; }

      float GetCenterRegionRatio() { return _centerRegionRatio; }
      void SetCenterRegionRatio(float lowerRegionRatio) { _centerRegionRatio = lowerRegionRatio; }

      int GetConsecutiveCount() { return _consecutiveCount; }
      void SetConsecutiveCount(int consecutiveCount) { _consecutiveCount = consecutiveCount; }

      int GetMaximumDistance() { return _maximumDistance; }
      void SetMaximumDistance(int maximumDistance) { _maximumDistance = maximumDistance; }

      int GetMaximumRadiusDiff() { return _maximumRadiusDiff; }
      void SetMaximumRadiusDiff(int maximumRadiusDiff) { _maximumRadiusDiff = maximumRadiusDiff; }

    private:
      // parameters specific to blob detector mode.
      BlobDetector::BlobDetectorParameters _blobDetectorParams;

      // parameters specific to deep learning mode.
      DeepLearning::DeepLearningParameters _deepLearningParams;

      // detection mode to use (CV or AI).
      Version _version;

      // upper region to inspect for traffic lights.
      float _upperRegionRatio;

      // horizontal fraction of image to analyze, centered.
      float _centerRegionRatio;

      // consecutive detection
      int _consecutiveCount;

      //  maximum distance and radius difference thresholds.
      int _maximumDistance;
      int _maximumRadiusDiff;
    };
  }
}