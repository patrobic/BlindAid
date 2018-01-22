#pragma once

#include "IModule.h"
#include "Capture.h"

#include "RealSense\SenseManager.h"

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
      void ReadCamera();
      void ConnectToCamera();
      void ValidateConnection();
      void InitializeCamera();
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