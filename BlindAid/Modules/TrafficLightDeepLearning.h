#pragma once

#include "TrafficLight.h"
#include <opencv2/dnn.hpp>
using namespace cv;
using namespace cv::dnn; 

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
		std::vector<cv::String> readClassNames(const char *filename);
		void getMaxClass(const cv::Mat &probBlob, int *classId, double *classProb);

		cv::String dependenciesPath;
		cv::String modelFile ;
		cv::String config ;
		cv::String imageFile ;
		cv::String inBlobName ;
		cv::String outBlobName ;
		cv::String classNamesFile ;

		dnn::Net net;

        cv::Mat _preprocessedImage;
        float _confidence[4];
      };
    }
  }
}