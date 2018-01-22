#include "CaptureRealtime.h"

#include <Windows.h>

using namespace std;
using namespace cv;
using namespace std::chrono;

namespace Capture
{
  namespace Realtime
  {
    Realtime::Realtime(IParameters *params, IData *input, IData *output) : Base(params, input, output)
    {
      cout << "[ CAMERA] Connecting to camera.\n";
      
      InitializeCamera();
    }

    void Realtime::InitializeCamera()
    {
      _pp = Intel::RealSense::SenseManager::CreateInstance();

      Intel::RealSense::DataDesc desc = {};
      desc.deviceInfo.streams = Intel::RealSense::Capture::STREAM_TYPE_COLOR | Intel::RealSense::Capture::STREAM_TYPE_DEPTH;
      _pp->EnableStreams(&desc);

      _pp->Init();
      Intel::RealSense::Capture::Device *device = _pp->QueryCaptureManager()->QueryDevice();

      *_output->GetColorImage() = Mat(_params->GetRealtimeParams()->GetColorResolution(), CV_8UC3, Mat::AUTO_STEP);
      *_output->GetDepthImage() = Mat(_params->GetRealtimeParams()->GetDepthResolution(), CV_16U, Mat::AUTO_STEP);
    }

    void Realtime::Process()
    {
      steady_clock::time_point start = steady_clock::now();

      ReadCamera();
      ConnectToCamera();

      if (_params->GetType() == SwitchableParameters::Type::Color || _params->GetType() == SwitchableParameters::Type::Both)
        GetColorFrame();
      if (_params->GetType() == SwitchableParameters::Type::Depth || _params->GetType() == SwitchableParameters::Type::Both)
        GetDepthFrame();

      _pp->ReleaseFrame();

      steady_clock::time_point end = steady_clock::now();
      duration<double> time_span = duration_cast<duration<double>>(end - start);
      cout << "[CAPTURE] Frame loaded (" << time_span.count() * 1000 << "ms).\n";
    }

    void Realtime::ReadCamera()
    {
      _pp->AcquireFrame(false);
      _sample = _pp->QuerySample();
    }

    void Realtime::ConnectToCamera()
    {
      while (_sample->color == NULL || _sample->depth == NULL)
      {
        cout << "[ CAMERA] Connection failed, waiting for camera.\n";
        Sleep(1000);
        
        InitializeCamera();
        ReadCamera();
      }

      cout << "[ CAMERA] Connection success.\n";
    }

    void Realtime::GetColorFrame()
    {
      _sample->color->AcquireAccess(Intel::RealSense::ImageAccess::ACCESS_READ, Intel::RealSense::PixelFormat::PIXEL_FORMAT_BGR, &_color);
      _output->GetColorImage()->data = _color.planes[0];

      CreateHsvImage();
      _sample->color->ReleaseAccess(&_color);
    }

    void Realtime::GetDepthFrame()
    {
      _sample->depth->AcquireAccess(Intel::RealSense::ImageAccess::ACCESS_READ, Intel::RealSense::PixelFormat::PIXEL_FORMAT_DEPTH, &_depth);
      Mat temp = Mat(_params->GetRealtimeParams()->GetDepthResolution(), CV_16U, _depth.planes[0]);

      temp(Rect(0, 0, 628, 468)).copyTo(*_output->GetDepthImage());
      _sample->color->ReleaseAccess(&_depth);
    }
  }
}