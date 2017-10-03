#pragma once

#include "IModule.h"

class CaptureSim : public IModule
{
public:
  void Init(Data *data);
  void operator()();

private:
  void VideoCaptureThread();
  void PhotoCaptureThread();

  cv::VideoCapture _cap;
};