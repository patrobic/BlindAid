#pragma once

#include "IModule.h"

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

  private:
    MediaType _mediaType = Photo;
    std::string _colorSimDataPath;
    std::string _depthSimDataPath;
  };

  class Results : public IResults
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

  CaptureBase(Data *data, IParameters *params, IResults *input, IResults *output)
  {
    _data = data;
    _params = static_cast<Parameters*>(params);
    _input = input;
    _output = static_cast<Results*>(output);
  }

  virtual void operator()() = 0;
  
  void CreateHsvImage()
  {
    cvtColor(*_output->GetRgbImage(), *_output->GetHsvImage(), CV_BGR2HSV);
  }

protected:
  Data *_data;
  Parameters *_params;
  IResults *_input;
  Results *_output;
};

class Capture : public CaptureBase
{
public:
  Capture(Data *data, IParameters *params, IResults *input, IResults *output) : CaptureBase(data, params, input, output) {}
  void operator()();

  // TODO: Implement class to communicate with camera capture SDK and store both color images in cv::Mat as they come in.
private:
};