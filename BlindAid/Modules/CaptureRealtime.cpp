#include "CaptureRealtime.h"

using namespace std;
using namespace cv;
using namespace rs2;

namespace Capture
{
  Realtime::Realtime(IParameters *params, IData *input, IData *output) : Base(params, input, output)
  {
    _cfg.enable_stream(RS2_STREAM_COLOR, 640, 480, RS2_FORMAT_BGR8, 30);

    if (_params->GetEnableDepth())
    {
      _cfg.enable_stream(RS2_STREAM_INFRARED, 640, 480, RS2_FORMAT_Y8, 30);
      _cfg.enable_stream(RS2_STREAM_DEPTH, 640, 480, RS2_FORMAT_Z16, 30);
    }

    _pipe.start(_cfg);

    *_output->GetRgbImage() = Mat(Size(640, 480), CV_8UC3, Mat::AUTO_STEP);
  }

  void Realtime::Process()
  {
    GetFrame();
  }

  void Realtime::GetFrame()
  {
    _frames = _pipe.wait_for_frames();
    _colorFrame = _frames.get_color_frame();

    _output->GetRgbImage()->data = (uchar*)_colorFrame.get_data();
    CreateHsvImage();

    if (_params->GetEnableDepth())
    {
      rs2::frame ir_frame = _frames.first(RS2_STREAM_INFRARED);
      rs2::frame depth_frame = _frames.get_depth_frame();
      Mat ir(Size(640, 480), CV_8UC1, (void*)ir_frame.get_data(), Mat::AUTO_STEP);

      equalizeHist(ir, ir);
      applyColorMap(ir, ir, COLORMAP_JET);

      *_output->GetDepthImage() = ir;
    }

    waitKey(1);
  }
}