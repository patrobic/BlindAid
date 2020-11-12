#pragma once

#include "IModule.h"
#include "Capture.h"

namespace Capture
{
  namespace Simulate
  {
    class CaptureSimulate : public Capture
    {
    public:
      CaptureSimulate(IParameters *params, IData *input, IData *output, Logger *logger);
      ~CaptureSimulate();

    private:
      void Process();
      void LoadImageFiles();
      void LoadColorStream();
      void LoadDepthStream();

      int _index = 0;
      std::string _colorName;
      std::string _depthName;
    };
  }
}