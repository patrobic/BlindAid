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
      Simulate(IParameters *params, IData *input, IData *output);

    private:
      void Process();
      void PrintDepthObstacle();
      void PrintTrafficLights();
      void PrintStopSign();

      cv::Mat _depthMat;
    };
  }
}