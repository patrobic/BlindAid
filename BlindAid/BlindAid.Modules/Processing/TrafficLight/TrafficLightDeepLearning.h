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
        DeepLearning(IParameters *params, IData *input, IData *output, Logger *logger);
        ~DeepLearning();

      private:
        void LoadNetwork();
        void Process();
        void CreateThread();
        void PreprocessImage();
        void MachineLearning();
        void UpdateResults();
        void ProcessFunc();

        void TProcess();
        std::thread *_processThread;

        cv::Mat _preprocessedImage;
        cv::Mat _inputBlob;
        cv::Mat _result;
        cv::dnn::Net _net;

        cv::Point _classNumber;
        int _classId;
        double _classProb;
        float _confidence[4];

        int _map[4] = { 3, 0, 1, 2 };

        bool _firstRun = true;
      };
    }
  }
}