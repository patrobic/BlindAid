#pragma once

#include "IParameters.h"

namespace Display
{
  class Parameters : public SwitchableParameters
  {
  public:
    Parameters(GlobalParameters *params) : SwitchableParameters(params)
    {
      Defaults();
    }

    void Defaults()
    {
      _colorWindowPosition = cv::Point(0, 0);
      _depthWindowPosition = cv::Point(800, 0);
      _colorWindowScale = 0.4f;
      _depthWindowScale = 1.0f;

      _toggle = Disabled;
    }

    bool Valid()
    {
      return true;
    }

    cv::Point GetColorWindowPosition() { return _colorWindowPosition; }
    void SetColorWindowPosition(cv::Point point) { _colorWindowPosition = point; }

    cv::Point GetDepthWindowPosition() { return _depthWindowPosition; }
    void SetDepthWindowPosition(cv::Point point) { _depthWindowPosition = point; }

    float GetColorWindowScale() { return _colorWindowScale; }
    void SetColorWindowScale(float scale) { _colorWindowScale = scale; }

    float GetDepthWindowScale() { return _depthWindowScale; }
    void SetDepthWindowScale(float scale) { _depthWindowScale = scale; }

  private:
    // position of color image window.
    cv::Point _colorWindowPosition;

    // position of depth image window
    cv::Point _depthWindowPosition;

    // scale of color image window.
    float _colorWindowScale;

    // scale of depth image window
    float _depthWindowScale;
  };
}