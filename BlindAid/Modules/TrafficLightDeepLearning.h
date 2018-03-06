#pragma once

#include "TrafficLight.h"

#include "opencv2/dnn.hpp"

namespace Vision
{
  namespace TrafficLight
  {
    namespace DeepLearning
    {
      class DeepLearning : public Base
      {
      public:
        DeepLearning(IParameters *params, IData *input, IData *output);

      private:
        void LoadNetwork();
        void Process();
        void PreprocessImage();
        void MachineLearning();
        void UpdateResults();

        cv::Mat _preprocessedImage;
        cv::Mat _inputBlob;
        cv::Mat _result;
        cv::dnn::Net _net;

        cv::Point _classNumber;
        int _classId;
        double _classProb;
        float _confidence[4];

        cv::String _path = "C:\\Projects\\BlindAid\\MachineLearning\\";
        int _map[4] = { 3, 0, 1, 2 };
      };
    }
  }
}