#pragma once

#include "IModule.h"
#include "Control.h"
#include "Vision.h"

namespace Control
{
  namespace Simulate
  {
    class ControlSimulate : public Control
    {
    public:
      ControlSimulate(IParameters *params, IData *input, IData *output, Tools::Logger *logger);
      ~ControlSimulate();

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