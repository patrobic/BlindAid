#include "SaveConfig.h"

SaveConfiguration::SaveConfiguration(Core::Parameters *params, std::string path)
{
  _params = params;
  _path = path;
}

void SaveConfiguration::operator()()
{
  Setting &root = _config.getRoot();

  Core(root.add("core", Setting::Type::TypeGroup), _params);

  _config.writeFile(_path.c_str());
}

void SaveConfiguration::Core(Setting &setting, Core::Parameters *parameters)
{
  Capture(setting.add("capture", Setting::Type::TypeGroup), _params->GetCaptureParams());
  Record(setting.add("record", Setting::Type::TypeGroup), _params->GetRecordParams());
  Vision(setting.add("vision", Setting::Type::TypeGroup), _params->GetVisionParams());
  Control(setting.add("control", Setting::Type::TypeGroup), _params->GetControlParams());
  Display(setting.add("display", Setting::Type::TypeGroup), _params->GetDisplayParams());
}

void SaveConfiguration::Capture(Setting &setting, Capture::Parameters *parameters)
{
  BaseParams(setting, parameters);

  CaptureRealtime(setting.add("realtime", Setting::Type::TypeGroup), parameters->GetRealtimeParams());
  CaptureSimulate(setting.add("simulate", Setting::Type::TypeGroup), parameters->GetSimulateParams());
}

void SaveConfiguration::CaptureRealtime(Setting &setting, Capture::Realtime::Parameters *parameters)
{

}

void SaveConfiguration::CaptureSimulate(Setting &setting, Capture::Simulate::Parameters *parameters)
{

}

void SaveConfiguration::Record(Setting &setting, Record::Parameters *parameters)
{
  BaseParams(setting, parameters);

}

void SaveConfiguration::Vision(Setting &setting, Vision::Parameters *parameters)
{
  BaseParams(setting, parameters);

  SaveDepthObstacle(setting.add("depthobstacle", Setting::Type::TypeGroup), parameters->GetDepthObstacleParams());
  SaveTrafficLight(setting.add("trafficlight", Setting::Type::TypeGroup), parameters->GetTrafficLightParams());
  SaveStopSign(setting.add("stopsign", Setting::Type::TypeGroup), parameters->GetStopSignParams());
}

void SaveConfiguration::Control(Setting &setting, Control::Parameters *parameters)
{
  BaseParams(setting, parameters);

  ControlRealtime(setting.add("realtime", Setting::Type::TypeGroup), parameters->GetRealtimeParams());
  ControlSimulate(setting.add("simulate", Setting::Type::TypeGroup), parameters->GetSimulateParams());
}

void SaveConfiguration::ControlRealtime(Setting &setting, Control::Realtime::Parameters *parameters)
{

}

void SaveConfiguration::ControlSimulate(Setting &setting, Control::Simulate::Parameters *parameters)
{

}

void SaveConfiguration::Display(Setting &setting, Display::Parameters *parameters)
{
  BaseParams(setting, parameters);

}

void SaveConfiguration::SaveDepthObstacle(Setting &setting, Vision::DepthObstacle::Parameters *parameters)
{
  BaseParams(setting, parameters);

}

void SaveConfiguration::SaveTrafficLight(Setting &setting, Vision::TrafficLight::Parameters *parameters)
{
  BaseParams(setting, parameters);

  TrafficLightBlobDetector(setting.add("blobdetector", Setting::Type::TypeGroup), parameters->GetBlobDetectorParams());
  TrafficLightDeepLearning(setting.add("deeplearning", Setting::Type::TypeGroup), parameters->GetDeepLearningParams());
}

void SaveConfiguration::TrafficLightBlobDetector(Setting &setting, Vision::TrafficLight::BlobDetector::Parameters *parameters)
{

}

void SaveConfiguration::TrafficLightDeepLearning(Setting &setting, Vision::TrafficLight::DeepLearning::Parameters *parameters)
{

}

void SaveConfiguration::SaveStopSign(Setting &setting, Vision::StopSign::Parameters *parameters)
{
  BaseParams(setting, parameters);

}

void SaveConfiguration::BaseParams(Setting &setting, IParameters *parameters)
{
  setting.add("mode", Setting::Type::TypeInt) = _params->GetMode();
  setting.add("toggle", Setting::Type::TypeInt) = _params->GetToggle();
}
