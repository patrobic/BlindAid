#include "CaptureRealtime.h"

#include <Windows.h>

using namespace std;
using namespace cv;
using namespace std::chrono;

#define NAME "CAPTURE"

namespace Capture
{
  namespace Realtime
  {
    Realtime::Realtime(IParameters *params, IData *input, IData *output, Logger *logger) : Base(params, input, output, logger)
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

      _start = steady_clock::now();

      if (_device == NULL || _sample->color == NULL || _sample->depth == NULL)
      {
        Reconnect();
        LOG(Warning, "Connected to camera successfully", "CAMERA");
      }

      ReadCamera();
      GetFrames();

      LOG(Info, "Images captured from camera", "REALTIME", _start);
    }

    void Realtime::ReadCamera()
    {
      _pp->AcquireFrame(false);
      _sample = _pp->QuerySample();
    }

    void Realtime::ConnectToCamera()
    {
      LOG(Warning, "Connecting to acquisition...", "CAMERA");
      
      Connect();

      Reconnect();

      LOG(Warning, "Connected to camera successfully", "CAMERA");
    }

    void Realtime::Connect()
    {
        InitializeCamera();
        ReadCamera();
    }

    void Realtime::Reconnect()
    {
      while (_device == NULL || _sample->color == NULL || _sample->depth == NULL)
      {
        LOG(Warning, "Acquisition connection failed, waiting for camera...", "CAMERA");
        Sleep(1000);

        InitializeCamera();
        ReadCamera();
      }
    }

    void Realtime::GetFrames()
    {
      _output->_colorImageMutex.lock();

      try {
        if (_params->GetGlobalParameters()->GetType() == Color || _params->GetGlobalParameters()->GetType() == Both)
          GetColorFrame();
        if (_params->GetGlobalParameters()->GetType() == Depth || _params->GetGlobalParameters()->GetType() == Both)
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