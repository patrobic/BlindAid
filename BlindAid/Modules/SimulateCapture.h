#pragma once

#include "IModule.h"
#include "ModuleCapture.h"

class CaptureSim : public CaptureBase
{
public:
  CaptureSim(IParameters *params, IData *input, IData *output) : CaptureBase(params, input, output) {};
  void operator()();

private:
  void LoadVideo();
  void LoadPhoto();

  cv::VideoCapture _cap;
  
  int _frame = 0;
};