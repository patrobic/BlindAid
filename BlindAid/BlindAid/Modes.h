#pragma once

#include "Class.h"

class Modes : public Class
{
public:
  Modes(Core::Parameters *params, Logger *logger);
  void Configure() = delete;

  void GetHelp();
  void BypassMenu();
  void CaptureOnly();
  void ControlOnly(std::vector<std::string> params);
  void SimulateMode(std::vector<std::string> params);
  void EnableRecord(std::vector<std::string> params);
  void EnableDisplay();
  void EnableVerbose(std::vector<std::string> params);
  void LowPerformance();
  void SetComPort(std::vector<std::string> params);
  void SetConsecutiveCount(std::vector<std::string> params);
  void DepthObstacleMode(std::vector<std::string> params);
  void TrafficLightMode(std::vector<std::string> params);
  void DisableColor();
  void DisableDepth();

private:
  bool FlagToInt(std::vector<std::string> param, int index, int &number);
  bool FlagToString(std::vector<std::string> param, int index, std::string &path);
  bool FlagToPath(std::vector<std::string> param, int index, std::string &path);
};
