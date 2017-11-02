#pragma once

#include <string>
#include <fstream>

#include "libconfig.h"

#include "..\Modules\IParameters.h"
#include "..\Modules\ModuleCore.h"

using namespace libconfig;

class SaveConfiguration
{
public:
  SaveConfiguration(Core::Parameters *params, std::string path)
  {
    _params = params;
    _path = path;
  }

  void operator()()
  {
    Setting &root = _config.getRoot();

    SaveCore(root.add("core", Setting::Type::TypeGroup), _params);

    _config.writeFile(_path.c_str());
  }

  void SaveCore(Setting &setting, Core::Parameters *parameters)
  {
    // TODO: potentially move these parameters to base Parameters class of capture and control base classes?
    setting.add("captureMode", Setting::Type::TypeInt) = _params->GetCaptureMode();
    setting.add("controlMode", Setting::Type::TypeInt) = _params->GetControlMode();

    SaveCapture(setting.add("capture", Setting::Type::TypeGroup), _params->GetCaptureParams());
    SaveVision(setting.add("vision", Setting::Type::TypeGroup), _params->GetVisionParams());
    SaveControl(setting.add("control", Setting::Type::TypeGroup), _params->GetControlParams());
    SaveDisplay(setting.add("display", Setting::Type::TypeGroup), _params->GetDisplayParams());
  }

  void SaveCapture(Setting &setting, Capture::Parameters *parameters)
  {

  }

  void SaveVision(Setting &setting, Vision::Parameters *parameters)
  {


    SaveDepthObstacle(setting.add("depthobstacle", Setting::Type::TypeGroup), parameters->GetDepthObstacleParams());
    SaveTrafficLight(setting.add("trafficlight", Setting::Type::TypeGroup), parameters->GetTrafficLightParams());
    SaveStopSign(setting.add("stopsign", Setting::Type::TypeGroup), parameters->GetStopSignParams());
  }

  void SaveControl(Setting &setting, Control::Parameters *parameters)
  {

  }

  void SaveDisplay(Setting &setting, Display::Parameters *parameters)
  {

  }

  void SaveDepthObstacle(Setting &setting, DetectDepthObstacle::Parameters *parameters)
  {

  }

  void SaveTrafficLight(Setting &setting, DetectTrafficLight::Parameters *parameters)
  {

  }

  void SaveStopSign(Setting &setting, DetectStopSign::Parameters *parameters)
  {

  }

private:
  Core::Parameters *_params;
  std::string _path;

  libconfig::Config _config;
  const Setting *_root;
  std::fstream _stream;
};