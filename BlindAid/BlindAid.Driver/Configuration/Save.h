#pragma once

#include "Class.h"
#include "libconfig.h"

using namespace libconfig;

class Save : public Class
{
public:
  Save(Core::Parameters *params, Logger *logger);
  void Configure();

private:
  void Core(Setting &setting, Core::Parameters *parameters);
  void Capture(Setting &setting, Capture::Parameters *parameters);
  void CaptureRealtime(Setting &setting, Capture::Realtime::Parameters *parameters);
  void CaptureSimulate(Setting &setting, Capture::Simulate::Parameters *parameters);
  void Record(Setting &setting, Record::Parameters *parameters);
  void Vision(Setting &setting, Vision::Parameters *parameters);
  void Control(Setting &setting, Control::Parameters *parameters);
  void ControlRealtime(Setting &setting, Control::Realtime::Parameters *parameters);
  void ControlSimulate(Setting &setting, Control::Simulate::Parameters *parameters);
  void Display(Setting &setting, Display::Parameters *parameters);
  void SaveDepthObstacle(Setting &setting, Vision::DepthObstacle::Parameters *parameters);
  void SaveTrafficLight(Setting &setting, Vision::TrafficLight::Parameters *parameters);
  void TrafficLightBlobDetector(Setting &setting, Vision::TrafficLight::BlobDetector::Parameters *parameters);
  void TrafficLightDeepLearning(Setting &setting, Vision::TrafficLight::DeepLearning::Parameters *parameters);
  void BaseParams(Setting &setting, IParameters *parameters);

  libconfig::Config _config;
};