#pragma once

#include "IModule.h"

namespace Capture
{
  class CaptureData : public IData
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

    std::atomic<bool> _newColorFrame = false;
    std::mutex _colorImageMutex;

  private:
    cv::Mat _rgbImage;
    cv::Mat _hsvImage;
    cv::Mat _depthImage;
  };
}