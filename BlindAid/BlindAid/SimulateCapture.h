#pragma once

#include "IModule.h"
#include "ModuleCapture.h"

class CaptureSim : public CaptureBase
{
public:
  void Init(Data *data, IParameters *params, IResults *input, IResults *output);
  void operator()();

private:
  void VideoCaptureThread();
  void PhotoCaptureThread();

  cv::VideoCapture _cap;
};