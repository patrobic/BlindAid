#pragma once

#include "Class.h"
#include "libconfig.h"

using namespace libconfig;

// TODO: this class must be unit-tested somehow, to ensure that ALL values are loaded, and done so correctly.
// define a sample test config.cfg, load it, and check all Parameters classes to ensure that desired values are found.

class LoadConfiguration : public Class
{
public:
  LoadConfiguration(Core::Parameters *params, Logger *logger);
  void Configure(std::string path);

private:
  // NOTE: if no values are loaded, parameters will retain their default values as defined in the class.
  // It is important that we find a way to ensure all parameters are loaded (i.e. none are forgotten in this class.

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

  void LoadDepthObstacle(Setting &setting, Vision::DepthObstacle::Parameters *parameters);

  void LoadTrafficLight(Setting &setting, Vision::TrafficLight::Parameters *parameters);
  void TrafficLightBlobDetector(Setting &setting, Vision::TrafficLight::BlobDetector::Parameters *parameters);
  void TrafficLightDeepLearning(Setting &setting, Vision::TrafficLight::DeepLearning::Parameters *parameters);

  void BaseParams(Setting &setting, IParameters *parameters);

private:
  std::string _path;
  libconfig::Config _config;
};