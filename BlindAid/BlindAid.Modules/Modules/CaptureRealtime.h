#pragma once

#include "IModule.h"
#include "Capture.h"

#include "RealSense\SenseManager.h"

namespace Capture
{
  namespace Realtime
  {
    class CaptureRealtime : public Capture
    {
    public:
      CaptureRealtime(IParameters *params, IData *input, IData *output, Tools::Logger *logger);
      ~CaptureRealtime();

    private:
      void Process();
      void ConnectToCamera();
      void Connect();
      void Reconnect();
      void InitializeCamera();

      void QueryCamera();
      void AcquireFrames();
      void GetColorFrame();
      void GetDepthFrame();

      Intel::RealSense::SenseManager *_pp;
      Intel::RealSense::Capture::Sample *_sample;
      Intel::RealSense::Capture::Device *_device;
      Intel::RealSense::ImageData _color;
      Intel::RealSense::ImageData _depth;
    };
  }
}