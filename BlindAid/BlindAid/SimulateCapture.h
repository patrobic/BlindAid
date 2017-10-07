#pragma once

#include "IModule.h"
#include "ModuleCapture.h"

class CaptureSim : public CaptureBase
{
public:
  CaptureSim(Data *data, IParameters *params, IResults *input, IResults *output) : CaptureBase(data, params, input, output) {};
  void operator()();

private:
  void LoadVideo();
  void LoadPhoto();

  cv::VideoCapture _cap;
  
  int _frame = 0;
};