#pragma once

#include "IParameters.h"
#include "opencv2\core.hpp"

namespace Capture
{
  namespace Realtime
  {
    class Parameters : public IParameters
    {
    public:
      bool Valid()
      {
        return true;
      }

      cv::Size GetColorResolution() { return _colorResolution; }
      void SetColorResolution(cv::Size colorResolution) { _colorResolution = colorResolution; }

      int GetColorFrameRate() { return _colorFrameRate; }
      void SetColorFrameRate(int colorFrameRate) { _colorFrameRate = colorFrameRate; }

      cv::Size GetDepthResolution() { return _depthResolution; }
      void SetDepthResolution(cv::Size depthResolution) { _depthResolution = depthResolution; }

      int GetDepthFrameRate() { return _depthFrameRate; }
      void SetDepthFrameRate(int depthFrameRate) { _depthFrameRate = depthFrameRate; }

    private:
      // color camera resolution.
      cv::Size _colorResolution = cv::Size(640, 480); //cv::Size(1920, 1080);

                                                      // color camera frame rate.
      int _colorFrameRate = 30;

      // depth camera resolution.
      cv::Size _depthResolution = cv::Size(640, 480);

      // depth camera frame rate.
      int _depthFrameRate = 30;
    };
  }

  namespace Simulate
  {
    class Parameters : public IParameters
    {
    public:
      enum MediaType
      {
        Photo,
        Video,
        Sequence
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

      bool GetEnableColor() { return _enableColor; }
      void SetEnableColor(bool enableColor) { _enableColor = enableColor; }

    private:
      // enable or disable depth camera acquisition.
      bool _enableDepth = true;

      // enable or disable color camera acquisition.
      bool _enableColor = true;

      // indicate whether simulation media is photo or video.
      MediaType _mediaType = Photo;

      // path to color image for simulation.
      std::string _colorSimDataPath;

      // path to depth image for simulation.
      std::string _depthSimDataPath;
    };
  }

  class Parameters : public SwitchableParameters
  {
  public:
    bool Valid()
    {
      return true;
    }

    Realtime::Parameters *GetRealtimeParams() { return &_realtimeParams; }

    Simulate::Parameters *GetSimulateParams() { return &_simulateParams; }

  private:
    // realtime capture parameters.
    Realtime::Parameters _realtimeParams;

    // simulate capture parametes.
    Simulate::Parameters _simulateParams;
  };
}