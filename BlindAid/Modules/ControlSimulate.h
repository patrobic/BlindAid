#pragma once

#include "IModule.h"
#include "Control.h"
#include "Vision.h"

namespace Control
{
  namespace Simulate
  {
    class Simulate : public Base
    {
    public:
      Simulate(IParameters *params, IData *input, IData *output, Logger *logger);

    private:
      void Process();
      void PrintResults();
      void PrintDepthObstacle();
      void PrintTrafficLights();

      cv::Mat _depthMat;
      cv::Mat _vibration;
    };
  }
}