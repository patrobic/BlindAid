#pragma once

#include "IModule.h"
#include "CaptureBase.h"

#include "librealsense2\rs.hpp"

namespace Capture
{
  namespace Realtime
  {

    class Realtime : public Base<Parameters>
    {
    public:
      Realtime(IParameters *params, IData *input, IData *output);

    private:
      void Process();
      void GetFrame();

      rs2::pipeline _pipe;
      rs2::config _cfg;
      rs2::frameset _frames;
      rs2::frame _colorFrame;

    };
  }
}