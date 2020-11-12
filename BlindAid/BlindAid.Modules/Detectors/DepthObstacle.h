#pragma once

#include "IDetect.h"
#include "Capture.h"
#include "DepthObstacleData.h"

#define DEPTH_RANGE 256

namespace Vision
{
  namespace DepthObstacle
  {
    class Base : public IDetect<DepthObstacleParameters, Capture::CaptureData, DepthObstacleData>
    {
    public:
      Base(IParameters *params, IData *input, IData *output, Tools::Logger *logger);
      virtual ~Base();
      static Base *Base::MakeDepthObstacle(IParameters *params, IData *input, IData *output, Tools::Logger *logger);

    protected:
      void FindMaxInRegions();
      void MaskShadows();
      void SeparateRegions();
      void FindConsecutiveMax();
      void MapVibrationValues();

      cv::Mat _maskImage;
      std::vector<cv::Mat> _lastImages;
      int _index;
    };
  }
}