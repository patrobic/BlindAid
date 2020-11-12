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
    CaptureRealtime::CaptureRealtime(IParameters *params, IData *input, IData *output, Logger *logger) : Capture(params, input, output, logger)
    {
      ConnectToCamera();
    }

    CaptureRealtime::~CaptureRealtime()
    {
      
    }

    void CaptureRealtime::Process()
    {
      _start = steady_clock::now();

      if (_device == NULL || _sample->color == NULL || _sample->depth == NULL)
        Reconnect();
      QueryCamera();
      AcquireFrames();

      LOG(Info, "Images captured from camera", "REALTIME", _start);
    }

    void CaptureRealtime::ConnectToCamera()
    {
      LOG(Warning, "Connecting to acquisition...", "CAMERA");

      Connect();
      Reconnect();
    }

    void CaptureRealtime::Connect()
    {
      InitializeCamera();
      QueryCamera();
    }

    void CaptureRealtime::Reconnect()
    {
      int counter = 0;
      while (_device == NULL || _sample->color == NULL || _sample->depth == NULL)
      {
        LOG(Warning, "Acquisition connection failed, waiting for camera...", "CAMERA");

        Sleep(RECONNECT_DELAY);
        InitializeCamera();
        QueryCamera();

        if (++counter >= NUM_RETRIES)
          throw exception("Acquisition reconnection failed, aborting (too many retries).");
      }

      LOG(Warning, "Connected to camera successfully", "CAMERA");
    }

    void CaptureRealtime::InitializeCamera()
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

    void CaptureRealtime::QueryCamera()
    {
      _output->SetStatus(true);

      _pp->AcquireFrame(false);
      _sample = _pp->QuerySample();

    }

    void CaptureRealtime::AcquireFrames()
    {
      _output->_colorImageMutex.lock();

      if (_sample->color == NULL || _sample->depth == NULL)
      {
        _output->_colorImageMutex.unlock();
        _output->SetStatus(false);
        return;
      }

      if ((_params->GetGlobalParameters()->GetType() & Color) == Color)
        GetColorFrame();
      if ((_params->GetGlobalParameters()->GetType() & Depth) == Depth)
        GetDepthFrame();

      _pp->ReleaseFrame();

      _output->_colorImageMutex.unlock();
      _output->_newColorFrame = true;
    }

    void CaptureRealtime::GetColorFrame()
    {
      _sample->color->AcquireAccess(Intel::RealSense::ImageAccess::ACCESS_READ, Intel::RealSense::PixelFormat::PIXEL_FORMAT_BGR, &_color);
      _output->GetColorImage()->data = _color.planes[0];

      _sample->color->ReleaseAccess(&_color);
    }

    void CaptureRealtime::GetDepthFrame()
    {
      _sample->depth->AcquireAccess(Intel::RealSense::ImageAccess::ACCESS_READ, Intel::RealSense::PixelFormat::PIXEL_FORMAT_DEPTH, &_depth);
      Mat temp = Mat(_params->GetRealtimeParams()->GetDepthResolution(), CV_16U, _depth.planes[0]);

      temp(Rect(0, 0, 628, 468)).copyTo(*_output->GetDepthImage());
      _sample->depth->ReleaseAccess(&_depth);
    }
  }
}