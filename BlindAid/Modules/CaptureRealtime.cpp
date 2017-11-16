#include "CaptureRealtime.h"

using namespace std;
using namespace cv;
using namespace rs2;

namespace Capture
{
  namespace Realtime
  {
    Realtime::Realtime(IParameters *params, IData *input, IData *output) : Base<Parameters>(params, input, output)
    {
      if (_params->GetEnableColor())
      {
        _cfg.enable_stream(RS2_STREAM_COLOR, _params->GetColorResolution().width, _params->GetColorResolution().height, RS2_FORMAT_BGR8, _params->GetDepthFrameRate());
      }

      if (_params->GetEnableDepth())
      {
        _cfg.enable_stream(RS2_STREAM_INFRARED, _params->GetDepthResolution().width, _params->GetDepthResolution().height, RS2_FORMAT_Y8, _params->GetDepthFrameRate());
        _cfg.enable_stream(RS2_STREAM_DEPTH, _params->GetDepthResolution().width, _params->GetDepthResolution().height, RS2_FORMAT_Z16, _params->GetDepthFrameRate());
      }

      _pipe.start(_cfg);

      *_output->GetRgbImage() = Mat(_params->GetColorResolution(), CV_8UC3, Mat::AUTO_STEP);
      *_output->GetDepthImage() = Mat(_params->GetDepthResolution(), CV_8UC1, Mat::AUTO_STEP);
    }

    void Realtime::Process()
    {
      GetFrame();
    }

    void Realtime::GetFrame()
    {
      if (_params->GetEnableColor())
      {
        _frames = _pipe.wait_for_frames();
        _colorFrame = _frames.get_color_frame();

        _output->GetRgbImage()->data = (uchar*)_colorFrame.get_data();
        CreateHsvImage();
      }

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
}