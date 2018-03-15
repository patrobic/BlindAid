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
      Parameters(GlobalParameters *params) : IParameters(params)
      {
        Defaults(); 
      }

      void Defaults()
      {
        _colorResolution = cv::Size(1920, 1080);
        _colorFrameRate = 30;
        _depthResolution = cv::Size(640, 480);
        _depthFrameRate = 30;
      }

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
      cv::Size _colorResolution;

      // color camera frame rate.
      int _colorFrameRate;

      // depth camera resolution.
      cv::Size _depthResolution;

      // depth camera frame rate.
      int _depthFrameRate;
    };
  }

  namespace Simulate
  {
    class Parameters : public IParameters
    {
    public:
      Parameters(GlobalParameters *params) : IParameters(params)
      {
        Defaults();
      }

      void Defaults()
      {
        _colorSimDataPath = "";
        _depthSimDataPath = "";
      }

      bool Valid()
      {
        return true;
      }

      std::string GetColorSimDataPath() { return _colorSimDataPath; }
      void SetColorSimDataPath(std::string colorSimDataPath) { _colorSimDataPath = colorSimDataPath; }

      std::string GetDepthSimDataPath() { return _depthSimDataPath; }
      void SetDepthSimDataPath(std::string depthSimDataPath) { _depthSimDataPath = depthSimDataPath; }

    private:
      // path to color image for simulation.
      std::string _colorSimDataPath;

      // path to depth image for simulation.
      std::string _depthSimDataPath;
    };
  }

  class Parameters : public SwitchableParameters
  {
  public:
    Parameters(GlobalParameters *params) : SwitchableParameters(params), _realtimeParams(params), _simulateParams(params)
    {
      Defaults();
    }

    void Defaults()
    {
      _realtimeParams.Defaults();
      _simulateParams.Defaults();
    }

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