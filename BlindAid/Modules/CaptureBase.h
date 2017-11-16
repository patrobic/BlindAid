#pragma once

#include "IModule.h"
#include "CaptureParams.h"

namespace Capture
{
  class Data : public IData
  {
  public:
    void Clear() {}
    bool Valid()
    {
      return true;
    }

    cv::Mat *GetRgbImage() { return &_rgbImage; }
    cv::Mat *GetHsvImage() { return &_hsvImage; }
    cv::Mat *GetDepthImage() { return &_depthImage; }

  private:
    cv::Mat _rgbImage;
    cv::Mat _hsvImage;
    cv::Mat _depthImage;
  };

  template<class Params>
  class Base : public IModule<Params, IData, Data>
  {
  public:
    Base(IParameters *params, IData *input, IData *output) : IModule(params, input, output)
    {

    }

  protected:
    void CreateHsvImage()
    {
      cvtColor(*_output->GetRgbImage(), *_output->GetHsvImage(), CV_BGR2HSV);
    }
  };

  IIModule *MakeCapture(Capture::Parameters *params, IData *input, IData *output);
}
