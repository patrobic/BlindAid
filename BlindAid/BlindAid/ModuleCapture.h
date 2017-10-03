#pragma once

#include "IModule.h"

class Capture : public IModule
{
public:
  void Init(Data *data);
  void operator()();

  // TODO: Implement class to communicate with camera capture SDK and store both color images in cv::Mat as they come in.
private:

};