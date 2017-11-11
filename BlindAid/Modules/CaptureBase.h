#pragma once

#include "IModule.h"

namespace Capture
{
  class Parameters : public IParameters
  {
  public:
    enum MediaType
    {
      Photo,
      Video
    };

    bool Valid()
    {
      return true;
    }

    MediaType GetMediaType() { return _mediaType; }
    void SetMediaType(MediaType mediaType) { _mediaType = mediaType; }

    std::string GetColorSimDataPath() { return _colorSimDataPath; }
    void SetColorSimDataPath(std::string colorSimDataPath) { _colorSimDataPath = colorSimDataPath; }
    std::string GetDepthSimDataPath() { return _depthSimDataPath; }
    void SetDepthSimDataPath(std::string depthSimDataPath) { _depthSimDataPath = depthSimDataPath; }

    bool GetEnableDepth() { return _enableDepth; }
    void SetEnableDepth(bool enableDepth) { _enableDepth = enableDepth; }

  private:
    // indicate whether simulation media is photo or video.
    MediaType _mediaType = Photo;

    // path to color image for simulation.
    std::string _colorSimDataPath;

    // path to depth image for simulation.
    std::string _depthSimDataPath;

    // enable or disable depth camera acquisition.
    bool _enableDepth = false;
  };

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
    static Base *MakeCapture(IParameters *params, IData *input, IData *output);

  protected:
    void CreateHsvImage();

  };
}