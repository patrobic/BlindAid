#pragma once

#include "TrafficLight.h"

namespace Vision
{
  namespace TrafficLight
  {
    namespace BlobDetector
    {
      class BlobDetector : public TrafficLight
      {
      public:
        BlobDetector(IParameters *params, IData *input, IData *output, Tools::Logger *logger);
        ~BlobDetector();

      private:
        void Process();
        void CreateHsvImage();
        void MaskColors();
        void PreprocessImages();
        void DetectBlobs();
        void ConfirmWithBox();

        cv::Mat _hsvChannels[3];
        cv::Mat _bgrChannels[3];
        cv::Mat &_h;
        cv::Mat &_s;
        cv::Mat &_v;
        cv::Mat &_r;
        cv::Mat &_g;
        cv::Mat &_b;
        cv::Mat _blobMask[3];
      };
    }
  }
}