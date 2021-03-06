#include "Load.h"

Load::Load(Core::CoreParameters *params, Tools::Logger *logger) : Class(params, logger)
{

}

void Load::Configure()
{
  // TODO: exception checking for file exists.
  _config.readFile((_params->GetGlobalParameters()->GetExePath() + _params->GetGlobalParameters()->_path).c_str());

  Setting &root = _config.getRoot();

  Core(root.lookup("core"), _params);
}

void Load::Core(Setting &setting, Core::CoreParameters *parameters)
{
  Capture(setting.lookup("capture"), _params->GetCaptureParams());
  Record(setting.lookup("record"), _params->GetRecordParams());
  Vision(setting.lookup("vision"), _params->GetVisionParams());
  Control(setting.lookup("control"), _params->GetControlParams());
  Display(setting.lookup("display"), _params->GetDisplayParams());
}

void Load::Capture(Setting &setting, Capture::CaptureParameters*parameters)
{
  BaseParams(setting, parameters);

  CaptureRealtime(setting.lookup("realtime"), parameters->GetRealtimeParams());
  CaptureSimulate(setting.lookup("simulate"), parameters->GetSimulateParams());
}

void Load::CaptureRealtime(Setting &setting, Capture::Realtime::CaptureRealtimeParameters *parameters)
{

}

void Load::CaptureSimulate(Setting &setting, Capture::Simulate::CaptureSimulateParameters *parameters)
{

}

void Load::Record(Setting &setting, Record::RecordParameters *parameters)
{
  BaseParams(setting, parameters);


}

void Load::Vision(Setting &setting, Vision::VisionParameters *parameters)
{
  BaseParams(setting, parameters);

  LoadDepthObstacle(setting.lookup("depthobstacle"), parameters->GetDepthObstacleParams());
  LoadTrafficLight(setting.lookup("trafficlight"), parameters->GetTrafficLightParams());
}

void Load::Control(Setting &setting, Control::ControlParameters *parameters)
{
  BaseParams(setting, parameters);

  ControlRealtime(setting.lookup("realtime"), parameters->GetRealtimeParams());
  ControlSimulate(setting.lookup("simulate"), parameters->GetSimulateParams());
}

void Load::ControlRealtime(Setting &setting, Control::Realtime::ControlRealtimeParameters *parameters)
{

}

void Load::ControlSimulate(Setting &setting, Control::Simulate::ControlSimulateParameters *parameters)
{

}

void Load::Display(Setting &setting, Display::DisplayParameters *parameters)
{
  BaseParams(setting, parameters);

}

void Load::LoadDepthObstacle(Setting &setting, Vision::DepthObstacle::DepthObstacleParameters *parameters)
{
  BaseParams(setting, parameters);

}

void Load::LoadTrafficLight(Setting &setting, Vision::TrafficLight::TrafficLightParameters *parameters)
{
  BaseParams(setting, parameters);

  TrafficLightBlobDetector(setting.lookup("blobdetector"), parameters->GetBlobDetectorParams());
  TrafficLightDeepLearning(setting.lookup("deeplearning"), parameters->GetDeepLearningParams());
}

void Load::TrafficLightBlobDetector(Setting &setting, Vision::TrafficLight::BlobDetector::BlobDetectorParameters *parameters)
{

}

void Load::TrafficLightDeepLearning(Setting &setting, Vision::TrafficLight::DeepLearning::DeepLearningParameters *parameters)
{

}

void Load::BaseParams(Setting &setting, IParameters *parameters)
{
  int mode;
  setting.lookupValue("mode", mode);

  int toggle;
  setting.lookupValue("toggle", toggle);

  _params->SetMode((Mode)mode);
  _params->SetToggle((Toggle)toggle);
}
