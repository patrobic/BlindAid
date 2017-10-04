#pragma once

#include <string>
#include <fstream>

#include "IParameters.h"
#include "ModuleCore.h"

class ConfigParser
{
public:
  void Init(Core::Parameters *params, std::string path)
  {
    _params = params;
    _path = path;
  }

  void operator()()
  {
    _stream.open(_path, std::fstream::in);

    if (!_stream.good())
      throw std::exception("cannot open file");
    
    Parse();
  }

  void Parse()
  {
    ParseCoreParams();
    ParseCaptureParams();
    ParseVisionParams();
    ParseControlParams();
    ParseDisplayParams();

    // TODO: implement INI file parsing (deserializing) class that reads file path 
  }

  void ParseCoreParams()
  {
    _params->SetCaptureMode(Core::Parameters::Mode::Realtime);
    _params->SetControlMode(Core::Parameters::Mode::Realtime);

  }

  void ParseCaptureParams()
  {
    Capture::Parameters *captureParams = _params->GetCaptureParams();

  }

  void ParseVisionParams()
  {
    Vision::Parameters *visionParams = _params->GetVisionParams();

  }

  void ParseControlParams()
  {
    Control::Parameters *controlParams = _params->GetControlParams();

  }

  void ParseDisplayParams()
  {
    Display::Parameters *displayParams = _params->GetDisplayParams();

  }

  void ParseDepthObstacleParams()
  {
    DetectDepthObstacle::Parameters *visionParams = _params->GetVisionParams()->GetDepthObstacleParams();

  }

  void ParseTrafficLightParams()
  {
    DetectTrafficLight::Parameters *visionParams = _params->GetVisionParams()->GetTrafficLightParams();

  }

  void ParseStopSignParams()
  {
    DetectStopSign::Parameters *visionParams = _params->GetVisionParams()->GetStopSignParams();

  }

private:
  Core::Parameters *_params;
  std::string _path;

  std::fstream _stream;
};