#pragma once

#include "Class.h"
#include "libconfig.h"

using namespace libconfig;

class Save : public Class
{
public:
  Save(Core::CoreParameters *params, Tools::Logger *logger);
  void Configure();

private:
  void Core(Setting &setting, Core::CoreParameters *parameters);
 
  void Capture(Setting &setting, Capture::CaptureParameters *parameters);
  void CaptureRealtime(Setting &setting, Capture::Realtime::CaptureRealtimeParameters *parameters);
  void CaptureSimulate(Setting &setting, Capture::Simulate::CaptureSimulateParameters *parameters);

  void Vision(Setting &setting, Vision::VisionParameters *parameters);

  void SaveDepthObstacle(Setting &setting, Vision::DepthObstacle::DepthObstacleParameters *parameters);
  void DepthObstacleFixedRegions(Setting& setting, Vision::DepthObstacle::FixedRegions::FixedRegionsParameters* parameters);
  void DepthObstacleHandPosition(Setting& setting, Vision::DepthObstacle::HandPosition::HandPositionParameters* parameters);

  void SaveTrafficLight(Setting &setting, Vision::TrafficLight::TrafficLightParameters *parameters);
  void TrafficLightBlobDetector(Setting &setting, Vision::TrafficLight::BlobDetector::BlobDetectorParameters *parameters);
  void TrafficLightDeepLearning(Setting &setting, Vision::TrafficLight::DeepLearning::DeepLearningParameters *parameters);

  void Control(Setting &setting, Control::ControlParameters *parameters);
  void ControlRealtime(Setting &setting, Control::Realtime::ControlRealtimeParameters *parameters);
  void ControlSimulate(Setting &setting, Control::Simulate::ControlSimulateParameters *parameters);

  void Display(Setting &setting, Display::DisplayParameters *parameters);
  void Record(Setting &setting, Record::RecordParameters *parameters);

  void BaseParams(Setting &setting, IParameters *parameters);

  libconfig::Config _config;
};