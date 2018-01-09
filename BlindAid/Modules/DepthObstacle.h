#pragma once

#include "IDetect.h"
#include "Capture.h"
#include "DepthObstacleData.h"

#define DEPTH_RANGE 256

namespace Vision
{
  namespace DepthObstacle
  {
    class Base : public IDetect<Parameters, Capture::Data, Data>
    {
    public:
      Base(IParameters *params, IData *input, IData *output);
      static Base *Base::MakeDepthObstacle(IParameters *params, IData *input, IData *output);

    protected:
      void MaskShadows();
      void SeparateRegions();
      void FindMaxInRegions();
      void MapVibrationValues();

      cv::Mat _grayImage;
      cv::Mat _maskImage;
    };
  }
}