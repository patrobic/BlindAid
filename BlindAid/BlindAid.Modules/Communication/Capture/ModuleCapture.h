#pragma once

#include "BaseCapture.h"

#include "librealsense2\rs.hpp"


class Capture : public CaptureBase
{
public:
  Capture(IParameters *params, IData *input, IData *output);
  void operator()();

private:
  void GetFrame();

  rs2::pipeline _pipe;
  rs2::config _cfg;
  rs2::frameset _frames;
  rs2::frame _colorFrame;
};