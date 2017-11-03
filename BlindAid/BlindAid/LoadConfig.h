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

    Core(root.lookup("core"), _params);
  }

  // NOTE: if no values are loaded, parameters will retain their default values as defined in the class.
  // It is important that we find a way to ensure all parameters are loaded (i.e. none are forgotten in this class.

private:
  void Core(Setting &setting, Core::Parameters *parameters)
  {
    Capture(setting.lookup("capture"), _params->GetCaptureParams());
    Record(setting.lookup("record"), _params->GetRecordParams());
    Vision(setting.lookup("vision"), _params->GetVisionParams());
    Control(setting.lookup("control"), _params->GetControlParams());
    Display(setting.lookup("display"), _params->GetDisplayParams());
  }

  void Capture(Setting &setting, Capture::Parameters *parameters)
  {
    BaseParams(setting, parameters);


  }

  void Record(Setting &setting, Record::Parameters *parameters)
  {
    BaseParams(setting, parameters);


  }

  void Vision(Setting &setting, Vision::Parameters *parameters)
  {
    BaseParams(setting, parameters);

    DepthObstacle(setting.lookup("depthobstacle"), parameters->GetDepthObstacleParams());
    TrafficLight(setting.lookup("trafficlight"), parameters->GetTrafficLightParams());
    StopSign(setting.lookup("stopsign"), parameters->GetStopSignParams());
  }

  void Control(Setting &setting, Control::Parameters *parameters)
  {
    BaseParams(setting, parameters);


  }

  void Display(Setting &setting, Display::Parameters *parameters)
  {
    BaseParams(setting, parameters);

  }

  void DepthObstacle(Setting &setting, DetectDepthObstacle::Parameters *parameters)
  {
    BaseParams(setting, parameters);

  }

  void TrafficLight(Setting &setting, DetectTrafficLight::Parameters *parameters)
  {
    BaseParams(setting, parameters);

  }

  void StopSign(Setting &setting, DetectStopSign::Parameters *parameters)
  {
    BaseParams(setting, parameters);

  }

  void BaseParams(Setting &setting, IParameters *parameters)
  {
    int mode;
    setting.lookupValue("mode", mode);

    int toggle;
    setting.lookupValue("toggle", toggle);

    _params->SetMode((IParameters::Mode)mode);
    _params->SetToggle((IParameters::Toggle)toggle);
  }

private:
  Core::Parameters *_params;
  std::string _path;

  libconfig::Config _config;
};