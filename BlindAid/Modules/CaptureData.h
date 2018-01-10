#pragma once

#include "IModule.h"

namespace Capture
{
  class Data : public IData
  {
  public:
    void Clear()
    {
    
    }

    bool Valid()
    {
      return true;
    }

    cv::Mat *GetColorImage() { return &_rgbImage; }
    cv::Mat *GetHsvImage() { return &_hsvImage; }
    cv::Mat *GetDepthImage() { return &_depthImage; }

  private:
    cv::Mat _rgbImage;
    cv::Mat _hsvImage;
    cv::Mat _depthImage;
  };
}