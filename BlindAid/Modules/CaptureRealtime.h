#pragma once

#include "IModule.h"
#include "CaptureBase.h"

#include "librealsense2\rs.hpp"

namespace Capture
{
  namespace Realtime
  {
    class Realtime : public Base
    {
    public:
      Realtime(IParameters *params, IData *input, IData *output);

    private:
      void Process();
      void ConnectToCamera();
      void GetColorFrame();
      void GetDepthFrame();

      rs2::pipeline _pipe;
      rs2::config _cfg;
      rs2::frameset _frames;
      rs2::frame _colorFrame;
      rs2::frame ir_frame;
      rs2::frame depth_frame;
    };
  }
}