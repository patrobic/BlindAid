#pragma once

#include "IModule.h"

#include "librealsense2\rs.hpp"

class CaptureBase : public IModule
{
public:
  class Parameters : public IParameters
  {
  public:
    enum MediaType
    {
      Photo,
      Video
    };

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

    cv::Mat *GetRgbImage() { return &_rgbImage; }
    cv::Mat *GetHsvImage() { return &_hsvImage; }
    cv::Mat *GetDepthImage() { return &_depthImage; }

  private:
    cv::Mat _rgbImage;
    cv::Mat _hsvImage;
    cv::Mat _depthImage;
  };

  CaptureBase(IParameters *params, IData *input, IData *output)
  {
    _params = static_cast<Parameters*>(params);
    _input = input;
    _output = static_cast<Data*>(output);
  }

  virtual void operator()() = 0;
  
protected:
  void CreateHsvImage()
  {
    cvtColor(*_output->GetRgbImage(), *_output->GetHsvImage(), CV_BGR2HSV);
  }

  Parameters *_params;
  IData *_input;
  Data *_output;
};

class Capture : public CaptureBase
{
public:
  Capture(IParameters *params, IData *input, IData *output);
  void operator()();

private:
  void GetFrame();

  rs2::pipeline _pipe;
  rs2::config _cfg;
  rs2::frameset _frames;
  rs2::frame _colorFrame;
};