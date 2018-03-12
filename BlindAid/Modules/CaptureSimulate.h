#pragma once

#include "IModule.h"
#include "Capture.h"

namespace Capture
{
  namespace Simulate
  {
    class Simulate : public Base
    {
    public:
      Simulate(IParameters *params, IData *input, IData *output, Logger *logger);

    private:
      void Process();
      void LoadFile();
      void LoadVideo();
      void LoadPhoto();
      void LoadSequence();

      cv::VideoCapture _cap;

      int _index = 0;
    };
  }
}