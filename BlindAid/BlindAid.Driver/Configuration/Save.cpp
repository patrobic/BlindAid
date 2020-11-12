#include "Save.h"

Save::Save(Core::CoreParameters *params, Tools::Logger *logger) : Class(params, logger)
{

}

void Save::Configure()
{
  Setting &root = _config.getRoot();

  Core(root.add("core", Setting::Type::TypeGroup), _params);

  _config.writeFile((_params->GetGlobalParameters()->GetExePath() + _params->GetGlobalParameters()->_path).c_str());
}

void Save::Core(Setting &setting, Core::CoreParameters *parameters)
{
  Capture(setting.add("capture", Setting::Type::TypeGroup), _params->GetCaptureParams());
  Record(setting.add("record", Setting::Type::TypeGroup), _params->GetRecordParams());
  Vision(setting.add("vision", Setting::Type::TypeGroup), _params->GetVisionParams());
  Control(setting.add("control", Setting::Type::TypeGroup), _params->GetControlParams());
  Display(setting.add("display", Setting::Type::TypeGroup), _params->GetDisplayParams());
}

void Save::Capture(Setting &setting, Capture::CaptureParameters *parameters)
{
  BaseParams(setting, parameters);

  CaptureRealtime(setting.add("realtime", Setting::Type::TypeGroup), parameters->GetRealtimeParams());
  CaptureSimulate(setting.add("simulate", Setting::Type::TypeGroup), parameters->GetSimulateParams());
}

void Save::CaptureRealtime(Setting &setting, Capture::Realtime::CaptureRealtimeParameters *parameters)
{

}

void Save::CaptureSimulate(Setting &setting, Capture::Simulate::CaptureSimulateParameters *parameters)
{

}

void Save::Record(Setting &setting, Record::RecordParameters *parameters)
{
  BaseParams(setting, parameters);

}

void Save::Vision(Setting &setting, Vision::VisionParameters *parameters)
{
  BaseParams(setting, parameters);

  SaveDepthObstacle(setting.add("depthobstacle", Setting::Type::TypeGroup), parameters->GetDepthObstacleParams());
  SaveTrafficLight(setting.add("trafficlight", Setting::Type::TypeGroup), parameters->GetTrafficLightParams());
}

void Save::Control(Setting &setting, Control::ControlParameters *parameters)
{
  BaseParams(setting, parameters);

  ControlRealtime(setting.add("realtime", Setting::Type::TypeGroup), parameters->GetRealtimeParams());
  ControlSimulate(setting.add("simulate", Setting::Type::TypeGroup), parameters->GetSimulateParams());
}

void Save::ControlRealtime(Setting &setting, Control::Realtime::ControlRealtimeParameters *parameters)
{

}

void Save::ControlSimulate(Setting &setting, Control::Simulate::ControlSimulateParameters *parameters)
{

}

void Save::Display(Setting &setting, Display::DisplayParameters *parameters)
{
  BaseParams(setting, parameters);

}

void Save::SaveDepthObstacle(Setting &setting, Vision::DepthObstacle::DepthObstacleParameters *parameters)
{
  BaseParams(setting, parameters);

  DepthObstacleFixedRegions(setting.add("fixedregions", Setting::Type::TypeGroup), parameters->GetFixedRegionsParams());
  DepthObstacleHandPosition(setting.add("handposition", Setting::Type::TypeGroup), parameters->GetHandPositionParams());
}

void Save::DepthObstacleFixedRegions(Setting& setting, Vision::DepthObstacle::FixedRegions::FixedRegionsParameters* parameters)
{

}

void Save::DepthObstacleHandPosition(Setting& setting, Vision::DepthObstacle::HandPosition::HandPositionParameters* parameters)
{

}

void Save::SaveTrafficLight(Setting &setting, Vision::TrafficLight::TrafficLightParameters *parameters)
{
  BaseParams(setting, parameters);

  TrafficLightBlobDetector(setting.add("blobdetector", Setting::Type::TypeGroup), parameters->GetBlobDetectorParams());
  TrafficLightDeepLearning(setting.add("deeplearning", Setting::Type::TypeGroup), parameters->GetDeepLearningParams());
}

void Save::TrafficLightBlobDetector(Setting &setting, Vision::TrafficLight::BlobDetector::BlobDetectorParameters *parameters)
{

}

void Save::TrafficLightDeepLearning(Setting &setting, Vision::TrafficLight::DeepLearning::DeepLearningParameters *parameters)
{

}

void Save::BaseParams(Setting &setting, IParameters *parameters)
{
  setting.add("mode", Setting::Type::TypeInt) = _params->GetMode();
  setting.add("toggle", Setting::Type::TypeInt) = _params->GetToggle();
}
