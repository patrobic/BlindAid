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
      ~Simulate();

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