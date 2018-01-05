#pragma once

#include "IModule.h"
#include "Vision.h"

namespace Display
{
  class Parameters : public SwitchableParameters
  {
  public:
    Parameters() { Defaults(); }

    void Defaults()
    {
      _colorWindowPosition = cv::Point(0, 0);
      _depthWindowPosition = cv::Point(800, 0);
      _vibrationWindowPosition = cv::Point(1000, 600);
      _colorWindowScale = 0.4f;
      _depthWindowScale = 1.0f;
      _vibrationWindowScale = 50.f;
    }

    bool Valid()
    {
      return true;
    }

    cv::Point GetColorWindowPosition() { return _colorWindowPosition; }
    void SetColorWindowPosition(cv::Point point) { _colorWindowPosition = point; }

    cv::Point GetDepthWindowPosition() { return _depthWindowPosition; }
    void SetDepthWindowPosition(cv::Point point) { _depthWindowPosition = point; }

    cv::Point GetVibrationWindowPosition() { return _vibrationWindowPosition; }
    void SetVibrationWindowPosition(cv::Point point) { _vibrationWindowPosition = point; }

    float GetColorWindowScale() { return _colorWindowScale; }
    void SetColorWindowScale(float scale) { _colorWindowScale = scale; }

    float GetDepthWindowScale() { return _depthWindowScale; }
    void SetDepthWindowScale(float scale) { _depthWindowScale = scale; }

    float GetVibrationWindowScale() { return _vibrationWindowScale; }
    void SetVibrationWindowScale(float scale) { _vibrationWindowScale = scale; }

  private:
    // position of color image window.
    cv::Point _colorWindowPosition;

    // position of depth image window
    cv::Point _depthWindowPosition;
  
    // position of color image window.
    cv::Point _vibrationWindowPosition;

    // scale of color image window.
    float _colorWindowScale;

    // scale of depth image window
    float _depthWindowScale;

    // scale of color image window.
    float _vibrationWindowScale;
  };

  class Data : public IData
  {
  public:
    void Clear() {}
    bool Valid()
    {
      return true;
    }

  private:

  };

  class Display : public IModule<Parameters, Vision::Data, Data>
  {
  public:
    Display(IParameters *params, IData *input, IData *output);

  private:
    void Process();
    void DrawDepthObstacles();
    void DrawTrafficLights();
    void DrawStopSign();
    void DisplayImage();

    cv::Mat _depthOverlay;
  };
}