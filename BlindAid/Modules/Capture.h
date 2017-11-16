#pragma once

#include "IModule.h"
#include "CaptureParameters.h"

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

  class Base : public IModule<Parameters, IData, Data>
  {
  public:
    Base(IParameters *params, IData *input, IData *output);
    static Base *MakeCapture(Capture::Parameters *params, IData *input, IData *output);

  protected:
    void CreateHsvImage();
  };
}
