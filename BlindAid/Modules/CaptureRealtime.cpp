#include "CaptureRealtime.h"

using namespace std;
using namespace cv;
using namespace std::chrono;
using namespace rs2;

namespace Capture
{
  namespace Realtime
  {
    Realtime::Realtime(IParameters *params, IData *input, IData *output) : Base(params, input, output)
    {
      ConnectToCamera();
    }

    void Realtime::ConnectToCamera()
    {
      if (_params->GetType() == SwitchableParameters::Type::Color || _params->GetType() == SwitchableParameters::Type::Both)
      {
        _cfg.enable_stream(RS2_STREAM_COLOR, _params->GetRealtimeParams()->GetColorResolution().width, _params->GetRealtimeParams()->GetColorResolution().height, RS2_FORMAT_BGR8, _params->GetRealtimeParams()->GetDepthFrameRate());
      }

      if (_params->GetType() == SwitchableParameters::Type::Depth || _params->GetType() == SwitchableParameters::Type::Both)
      {
        _cfg.enable_stream(RS2_STREAM_INFRARED, _params->GetRealtimeParams()->GetDepthResolution().width, _params->GetRealtimeParams()->GetDepthResolution().height, RS2_FORMAT_Y8, _params->GetRealtimeParams()->GetDepthFrameRate());
        _cfg.enable_stream(RS2_STREAM_DEPTH, _params->GetRealtimeParams()->GetDepthResolution().width, _params->GetRealtimeParams()->GetDepthResolution().height, RS2_FORMAT_Z16, _params->GetRealtimeParams()->GetDepthFrameRate());
      }

      _pipe.start(_cfg);

      *_output->GetRgbImage() = Mat(_params->GetRealtimeParams()->GetColorResolution(), CV_8UC3, Mat::AUTO_STEP);
      *_output->GetDepthImage() = Mat(_params->GetRealtimeParams()->GetDepthResolution(), CV_8UC1, Mat::AUTO_STEP);
    }

    void Realtime::Process()
    {
      steady_clock::time_point start = steady_clock::now();

      if (_params->GetType() == SwitchableParameters::Type::Color || _params->GetType() == SwitchableParameters::Type::Both)
        GetColorFrame();
      if (_params->GetType() == SwitchableParameters::Type::Depth || _params->GetType() == SwitchableParameters::Type::Both)
        GetDepthFrame();

      steady_clock::time_point end = steady_clock::now();
      duration<double> time_span = duration_cast<duration<double>>(end - start);
      cout << "[CAPTURE] Frame loaded (" << time_span.count() * 1000 << "ms).\n";
    }

    void Realtime::GetColorFrame()
    {
      _frames = _pipe.wait_for_frames();
      _colorFrame = _frames.get_color_frame();

      _output->GetRgbImage()->data = (uchar*)_colorFrame.get_data();

      CreateHsvImage();
    }

    void Realtime::GetDepthFrame()
    {
      ir_frame = _frames.first(RS2_STREAM_INFRARED);
      depth_frame = _frames.get_depth_frame();
      _output->GetDepthImage()->data = (uchar*)ir_frame.get_data();

      equalizeHist(*_output->GetDepthImage(), *_output->GetDepthImage());
      applyColorMap(*_output->GetDepthImage(), *_output->GetDepthImage(), COLORMAP_JET);
    }
  }
}