#pragma once

#include <string>
#include <fstream>

#include "libconfig.h"

#include "..\Modules\IParameters.h"
#include "..\Modules\ModuleCore.h"

using namespace libconfig;

// TODO: this class must be unit-tested somehow, to ensure that ALL values are loaded, and done so correctly.
// define a sample test config.cfg, load it, and check all Parameters classes to ensure that desired values are found.

class LoadConfiguration
{
public:
  LoadConfiguration(Core::Parameters *params, std::string path)
  {
    _params = params;
    _path = path;
  }

  void operator()()
  {
    // TODO: exception checking for file exists.
	  _config.readFile(_path.c_str());
    
    Setting &root = _config.getRoot();

    LoadCore(root.lookup("core"), _params);
  }

  // NOTE: if no values are loaded, parameters will retain their default values as defined in the class.
  // It is important that we find a way to ensure all parameters are loaded (i.e. none are forgotten in this class.

  void LoadCore(Setting &setting, Core::Parameters *parameters)
  {
	  int captureMode;
    setting.lookupValue("captureMode", captureMode);
	  int controlMode;
    setting.lookupValue("controlMode", controlMode);

	  _params->SetCaptureMode((Core::Parameters::Mode)captureMode);
	  _params->SetControlMode((Core::Parameters::Mode)controlMode);

    LoadCapture(setting.lookup("capture"), _params->GetCaptureParams());
    LoadVision(setting.lookup("vision"), _params->GetVisionParams());
    LoadControl(setting.lookup("control"), _params->GetControlParams());
    LoadDisplay(setting.lookup("display"), _params->GetDisplayParams());
  }

  void LoadCapture(Setting &setting, Capture::Parameters *parameters)
  {

  }

  void LoadVision(Setting &setting, Vision::Parameters *parameters)
  {


    LoadDepthObstacle(setting.lookup("depthobstacle"), parameters->GetDepthObstacleParams());
    LoadTrafficLight(setting.lookup("trafficlight"), parameters->GetTrafficLightParams());
    LoadStopSign(setting.lookup("stopsign"), parameters->GetStopSignParams());
  }

  void LoadControl(Setting &setting, Control::Parameters *parameters)
  {

  }

  void LoadDisplay(Setting &setting, Display::Parameters *parameters)
  {

  }

  void LoadDepthObstacle(Setting &setting, DetectDepthObstacle::Parameters *parameters)
  {

  }

  void LoadTrafficLight(Setting &setting, DetectTrafficLight::Parameters *parameters)
  {

  }

  void LoadStopSign(Setting &setting, DetectStopSign::Parameters *parameters)
  {

  }

private:
  Core::Parameters *_params;
  std::string _path;

  libconfig::Config _config;
};