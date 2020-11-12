#include "Save.h"

Save::Save(Core::Parameters *params, Logger *logger) : Class(params, logger)
{

}

void Save::Configure()
{
  Setting &root = _config.getRoot();

  Core(root.add("core", Setting::Type::TypeGroup), _params);

  _config.writeFile((_params->GetGlobalParameters()->GetExePath() + _params->GetGlobalParameters()->_path).c_str());
}

void Save::Core(Setting &setting, Core::Parameters *parameters)
{
  Capture(setting.add("capture", Setting::Type::TypeGroup), _params->GetCaptureParams());
  Record(setting.add("record", Setting::Type::TypeGroup), _params->GetRecordParams());
  Vision(setting.add("vision", Setting::Type::TypeGroup), _params->GetVisionParams());
  Control(setting.add("control", Setting::Type::TypeGroup), _params->GetControlParams());
  Display(setting.add("display", Setting::Type::TypeGroup), _params->GetDisplayParams());
}

void Save::Capture(Setting &setting, Capture::Parameters *parameters)
{
  BaseParams(setting, parameters);

  CaptureRealtime(setting.add("realtime", Setting::Type::TypeGroup), parameters->GetRealtimeParams());
  CaptureSimulate(setting.add("simulate", Setting::Type::TypeGroup), parameters->GetSimulateParams());
}

void Save::CaptureRealtime(Setting &setting, Capture::Realtime::Parameters *parameters)
{

}

void Save::CaptureSimulate(Setting &setting, Capture::Simulate::Parameters *parameters)
{

}

void Save::Record(Setting &setting, Record::Parameters *parameters)
{
  BaseParams(setting, parameters);

}

void Save::Vision(Setting &setting, Vision::Parameters *parameters)
{
  BaseParams(setting, parameters);

  SaveDepthObstacle(setting.add("depthobstacle", Setting::Type::TypeGroup), parameters->GetDepthObstacleParams());
  SaveTrafficLight(setting.add("trafficlight", Setting::Type::TypeGroup), parameters->GetTrafficLightParams());
}

void Save::Control(Setting &setting, Control::Parameters *parameters)
{
  BaseParams(setting, parameters);

  ControlRealtime(setting.add("realtime", Setting::Type::TypeGroup), parameters->GetRealtimeParams());
  ControlSimulate(setting.add("simulate", Setting::Type::TypeGroup), parameters->GetSimulateParams());
}

void Save::ControlRealtime(Setting &setting, Control::Realtime::Parameters *parameters)
{

}

void Save::ControlSimulate(Setting &setting, Control::Simulate::Parameters *parameters)
{

}

void Save::Display(Setting &setting, Display::Parameters *parameters)
{
  BaseParams(setting, parameters);

}

void Save::SaveDepthObstacle(Setting &setting, Vision::DepthObstacle::Parameters *parameters)
{
  BaseParams(setting, parameters);

}

void Save::SaveTrafficLight(Setting &setting, Vision::TrafficLight::Parameters *parameters)
{
  BaseParams(setting, parameters);

  TrafficLightBlobDetector(setting.add("blobdetector", Setting::Type::TypeGroup), parameters->GetBlobDetectorParams());
  TrafficLightDeepLearning(setting.add("deeplearning", Setting::Type::TypeGroup), parameters->GetDeepLearningParams());
}

void Save::TrafficLightBlobDetector(Setting &setting, Vision::TrafficLight::BlobDetector::Parameters *parameters)
{

}

void Save::TrafficLightDeepLearning(Setting &setting, Vision::TrafficLight::DeepLearning::Parameters *parameters)
{

}

void Save::BaseParams(Setting &setting, IParameters *parameters)
{
  setting.add("mode", Setting::Type::TypeInt) = _params->GetMode();
  setting.add("toggle", Setting::Type::TypeInt) = _params->GetToggle();
}
