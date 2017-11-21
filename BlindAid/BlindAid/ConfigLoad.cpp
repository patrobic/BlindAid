#include "ConfigLoad.h"

LoadConfiguration::LoadConfiguration(Core::Parameters *params, std::string path)
{
  _params = params;
  _path = path;
}

void LoadConfiguration::operator()()
{
  // TODO: exception checking for file exists.
  _config.readFile(_path.c_str());

  Setting &root = _config.getRoot();

  Core(root.lookup("core"), _params);
}

void LoadConfiguration::Core(Setting &setting, Core::Parameters *parameters)
{
  Capture(setting.lookup("capture"), _params->GetCaptureParams());
  Record(setting.lookup("record"), _params->GetRecordParams());
  Vision(setting.lookup("vision"), _params->GetVisionParams());
  Control(setting.lookup("control"), _params->GetControlParams());
  Display(setting.lookup("display"), _params->GetDisplayParams());
}

void LoadConfiguration::Capture(Setting &setting, Capture::Parameters *parameters)
{
  BaseParams(setting, parameters);

  CaptureRealtime(setting.lookup("realtime"), parameters->GetRealtimeParams());
  CaptureSimulate(setting.lookup("simulate"), parameters->GetSimulateParams());
}

void LoadConfiguration::CaptureRealtime(Setting &setting, Capture::Realtime::Parameters *parameters)
{

}

void LoadConfiguration::CaptureSimulate(Setting &setting, Capture::Simulate::Parameters *parameters)
{

}

void LoadConfiguration::Record(Setting &setting, Record::Parameters *parameters)
{
  BaseParams(setting, parameters);


}

void LoadConfiguration::Vision(Setting &setting, Vision::Parameters *parameters)
{
  BaseParams(setting, parameters);

  LoadDepthObstacle(setting.lookup("depthobstacle"), parameters->GetDepthObstacleParams());
  LoadTrafficLight(setting.lookup("trafficlight"), parameters->GetTrafficLightParams());
  LoadStopSign(setting.lookup("stopsign"), parameters->GetStopSignParams());
}

void LoadConfiguration::Control(Setting &setting, Control::Parameters *parameters)
{
  BaseParams(setting, parameters);

  ControlRealtime(setting.lookup("realtime"), parameters->GetRealtimeParams());
  ControlSimulate(setting.lookup("simulate"), parameters->GetSimulateParams());
}

void LoadConfiguration::ControlRealtime(Setting &setting, Control::Realtime::Parameters *parameters)
{

}

void LoadConfiguration::ControlSimulate(Setting &setting, Control::Simulate::Parameters *parameters)
{

}

void LoadConfiguration::Display(Setting &setting, Display::Parameters *parameters)
{
  BaseParams(setting, parameters);

}

void LoadConfiguration::LoadDepthObstacle(Setting &setting, Vision::DepthObstacle::Parameters *parameters)
{
  BaseParams(setting, parameters);

}

void LoadConfiguration::LoadTrafficLight(Setting &setting, Vision::TrafficLight::Parameters *parameters)
{
  BaseParams(setting, parameters);

  TrafficLightBlobDetector(setting.lookup("blobdetector"), parameters->GetBlobDetectorParams());
  TrafficLightDeepLearning(setting.lookup("deeplearning"), parameters->GetDeepLearningParams());
}

void LoadConfiguration::TrafficLightBlobDetector(Setting &setting, Vision::TrafficLight::BlobDetector::Parameters *parameters)
{

}

void LoadConfiguration::TrafficLightDeepLearning(Setting &setting, Vision::TrafficLight::DeepLearning::Parameters *parameters)
{

}

void LoadConfiguration::LoadStopSign(Setting &setting, Vision::StopSign::Parameters *parameters)
{
  BaseParams(setting, parameters);

}

void LoadConfiguration::BaseParams(Setting &setting, IParameters *parameters)
{
  int mode;
  setting.lookupValue("mode", mode);

  int toggle;
  setting.lookupValue("toggle", toggle);

  _params->SetMode((SwitchableParameters::Mode)mode);
  _params->SetToggle((SwitchableParameters::Toggle)toggle);
}
