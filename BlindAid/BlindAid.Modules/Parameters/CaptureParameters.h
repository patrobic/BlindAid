#pragma once

#include "IParameters.h"
#include "opencv2\core.hpp"

namespace Capture
{
  namespace Realtime
  {
    class CaptureRealtimeParameters : public IParameters
    {
    public:
      CaptureRealtimeParameters(GlobalParameters *params) : IParameters(params)
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
    class CaptureSimulateParameters : public IParameters
    {
    public:
      CaptureSimulateParameters(GlobalParameters *params) : IParameters(params)
      {
        Defaults();
      }

      void Defaults()
      {
        _colorSimDataPath = "";
        _depthSimDataPath = "";
        _startIndex = 0;
        _endIndex = INT_MAX;
      }

      bool Valid()
      {
        return true;
      }

      std::string GetColorSimDataPath() { return _colorSimDataPath; }
      void SetColorSimDataPath(std::string colorSimDataPath) { _colorSimDataPath = colorSimDataPath; }

      std::string GetDepthSimDataPath() { return _depthSimDataPath; }
      void SetDepthSimDataPath(std::string depthSimDataPath) { _depthSimDataPath = depthSimDataPath; }

      int GetStartIndex() { return _startIndex; }
      void SetStartIndex(int startIndex) { _startIndex = startIndex; }

      int GetEndIndex() { return _endIndex; }
      void SetEndIndex(int endIndex) { _endIndex = endIndex; }

    private:
      // path to color image for simulation.
      std::string _colorSimDataPath;

      // path to depth image for simulation.
      std::string _depthSimDataPath;

      // the index of the first image to load in a series.
      int _startIndex;

      // the index of the last image to load in a series.
      int _endIndex;
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

    Realtime::CaptureRealtimeParameters *GetRealtimeParams() { return &_realtimeParams; }

    Simulate::CaptureSimulateParameters *GetSimulateParams() { return &_simulateParams; }

  private:
    // realtime capture parameters.
    Realtime::CaptureRealtimeParameters _realtimeParams;

    // simulate capture parametes.
    Simulate::CaptureSimulateParameters _simulateParams;
  };
}