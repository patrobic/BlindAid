#pragma once

#include "IParameters.h"
#include "opencv2\core.hpp"

namespace Capture
{
  namespace Realtime
  {
    class RealtimeCaptureParameters : public IParameters
    {
    public:
      RealtimeCaptureParameters(GlobalParameters *params) : IParameters(params)
      {
        Defaults(); 
      }

      void Defaults()
      {
        _colorResolution = cv::Size(1920, 1080);
        _depthResolution = cv::Size(640, 480);
      }

      bool Valid()
      {
        return true;
      }

      cv::Size GetColorResolution() { return _colorResolution; }
      void SetColorResolution(cv::Size colorResolution) { _colorResolution = colorResolution; }

      cv::Size GetDepthResolution() { return _depthResolution; }
      void SetDepthResolution(cv::Size depthResolution) { _depthResolution = depthResolution; }

    private:
      // color camera resolution.
      cv::Size _colorResolution;

      // depth camera resolution.
      cv::Size _depthResolution;
    };
  }

  namespace Simulate
  {
    class SimulateCaptureParameters : public IParameters
    {
    public:
      SimulateCaptureParameters(GlobalParameters *params) : IParameters(params)
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

  class CaptureParameters : public SwitchableParameters
  {
  public:
    CaptureParameters(GlobalParameters *params) : SwitchableParameters(params), _realtimeParams(params), _simulateParams(params)
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

    Realtime::RealtimeCaptureParameters *GetRealtimeParams() { return &_realtimeParams; }

    Simulate::SimulateCaptureParameters *GetSimulateParams() { return &_simulateParams; }

  private:
    // realtime capture parameters.
    Realtime::RealtimeCaptureParameters _realtimeParams;

    // simulate capture parametes.
    Simulate::SimulateCaptureParameters _simulateParams;
  };
}