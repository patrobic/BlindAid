#pragma once

#include "Class.h"
#include "libconfig.h"

#include <VisionParameters.h>

using namespace libconfig;

class Load : public Class
{
public:
  Load(Core::CoreParameters *params, Tools::Logger *logger);
  void Configure();

private:
  void Core(Setting &setting, Core::CoreParameters *parameters);
  void Capture(Setting &setting, Capture::CaptureParameters *parameters);
  void CaptureRealtime(Setting &setting, Capture::Realtime::CaptureRealtimeParameters *parameters);
  void CaptureSimulate(Setting &setting, Capture::Simulate::CaptureSimulateParameters *parameters);
  void Record(Setting &setting, Record::RecordParameters *parameters);
  void Vision(Setting &setting, Vision::VisionParameters *parameters);
  void Control(Setting &setting, Control::ControlParameters *parameters);
  void ControlRealtime(Setting &setting, Control::Realtime::ControlRealtimeParameters *parameters);
  void ControlSimulate(Setting &setting, Control::Simulate::ControlSimulateParameters *parameters);
  void Display(Setting &setting, Display::DisplayParameters *parameters);
  void LoadDepthObstacle(Setting &setting, Vision::DepthObstacle::DepthObstacleParameters *parameters);
  void LoadTrafficLight(Setting &setting, Vision::TrafficLight::TrafficLightParameters *parameters);
  void TrafficLightBlobDetector(Setting &setting, Vision::TrafficLight::BlobDetector::BlobDetectorParameters *parameters);
  void TrafficLightDeepLearning(Setting &setting, Vision::TrafficLight::DeepLearning::DeepLearningParameters *parameters);
  void BaseParams(Setting &setting, IParameters *parameters);

  libconfig::Config _config;
};