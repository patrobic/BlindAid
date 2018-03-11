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
      ConnectToCamera();
    }

    void Realtime::InitializeCamera()
    {
      _pp = Intel::RealSense::SenseManager::CreateInstance();

      Intel::RealSense::DataDesc desc = {};
      desc.deviceInfo.streams = Intel::RealSense::Capture::STREAM_TYPE_COLOR | Intel::RealSense::Capture::STREAM_TYPE_DEPTH;
      _pp->EnableStreams(&desc);

      _pp->Init();
      _device = _pp->QueryCaptureManager()->QueryDevice();

      *_output->GetColorImage() = Mat(_params->GetRealtimeParams()->GetColorResolution(), CV_8UC3, Mat::AUTO_STEP);
      *_output->GetDepthImage() = Mat(_params->GetRealtimeParams()->GetDepthResolution(), CV_16U, Mat::AUTO_STEP);
    }

    void Realtime::Process()
    {
      _output->SetStatus(true);

      steady_clock::time_point start = steady_clock::now();

      ConnectToCamera();
      ReadCamera();
      GetFrames();

      steady_clock::time_point end = steady_clock::now();
      duration<double> time_span = duration_cast<duration<double>>(end - start);
      cout << "[CAPTURE] Images captured from camera.\t(" << setw(5) << (int)(time_span.count() * 1000) << " ms)\n";
    }

    void Realtime::ReadCamera()
    {
      _pp->AcquireFrame(false);
      _sample = _pp->QuerySample();
    }

    void Realtime::ConnectToCamera()
    {
      if (_device != NULL && _sample->color != NULL && _sample->depth != NULL)
        return;

      static bool firstConnect = true;
      if (firstConnect)
      {
        cout << "[ CAMERA] Connecting to acquisition...\n";
        InitializeCamera();
        ReadCamera();
        firstConnect = false;
      }
      else
      {
        while (_device == NULL || _sample->color == NULL || _sample->depth == NULL)
        {
          cout << "[ CAMERA] Acquisition connection failed, waiting for camera...\n";
          Sleep(1000);

          InitializeCamera();
          ReadCamera();
        }
      }

      cout << "[ CAMERA] Connected to acquisition successfully.\n";
    }

    void Realtime::GetFrames()
    {
      _output->_colorImageMutex.lock();
      
      try {
        if (_params->GetType() == SwitchableParameters::Type::Color || _params->GetType() == SwitchableParameters::Type::Both)
          GetColorFrame();
        if (_params->GetType() == SwitchableParameters::Type::Depth || _params->GetType() == SwitchableParameters::Type::Both)
          GetDepthFrame();
      }
      catch (...) {
        _output->_colorImageMutex.unlock();
        _output->SetStatus(false);
      }

      _pp->ReleaseFrame();

      _output->_colorImageMutex.unlock();
      _output->_newColorFrame = true;
    }

    void Realtime::GetColorFrame()
    {
      if (_sample->color == NULL) throw exception();

      _sample->color->AcquireAccess(Intel::RealSense::ImageAccess::ACCESS_READ, Intel::RealSense::PixelFormat::PIXEL_FORMAT_BGR, &_color);
      _output->GetColorImage()->data = _color.planes[0];

      CreateHsvImage();
      _sample->color->ReleaseAccess(&_color);
    }

    void Realtime::GetDepthFrame()
    {
      if (_sample->depth == NULL) throw exception();

      _sample->depth->AcquireAccess(Intel::RealSense::ImageAccess::ACCESS_READ, Intel::RealSense::PixelFormat::PIXEL_FORMAT_DEPTH, &_depth);
      Mat temp = Mat(_params->GetRealtimeParams()->GetDepthResolution(), CV_16U, _depth.planes[0]);

      temp(Rect(0, 0, 628, 468)).copyTo(*_output->GetDepthImage());
      _sample->depth->ReleaseAccess(&_depth);
    }
  }
}