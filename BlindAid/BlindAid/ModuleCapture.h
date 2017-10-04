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

    cv::Mat *GetColorImage() { return &_colorImage; }
    cv::Mat *GetDepthImage() { return &_depthImage; }

  private:
    cv::Mat _colorImage;
    cv::Mat _depthImage;

  };

  virtual void Init(Data *data, IParameters *params, IResults *input, IResults *output) = 0;
  virtual void operator()() = 0;

protected:
  Data *_data;
  Parameters *_params;
  IResults *_input;
  Results *_output;
};

class Capture : public CaptureBase
{
public:
  void Init(Data *data, IParameters *params, IResults *input, IResults *output);
  void operator()();

  // TODO: Implement class to communicate with camera capture SDK and store both color images in cv::Mat as they come in.
private:
};