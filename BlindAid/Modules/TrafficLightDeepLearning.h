#pragma once

#include "TrafficLight.h"
#include "Python.h"

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
        void Process();
        void PreprocessImage();
        void RunDeepLearning();

        void UpdateResults();

        cv::Mat _preprocessedImage;

        PyObject *_pyColorImage;
        PyObject *_pyConfidence[4];
        float _confidence[4];
      };
    }
  }
}