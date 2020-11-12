#pragma once

#include "Class.h"

class Modes : public Class
{
public:
  Modes(Core::CoreParameters *params, Tools::Logger *logger);
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
  void SetDepthFrameSmoothing(std::vector<std::string> params);
  void SetConfidence(std::vector<std::string> params);
  void SetTLRegion(std::vector<std::string> params);
  void SetDORegion(std::vector<std::string> params);
  void SetPercentileToIgnore(std::vector<std::string> params);
  void SetValidRatioThreshold(std::vector<std::string> params);

  static bool FlagToInt(std::vector<std::string> param, int index, int &number);
  bool FlagToFloat(std::vector<std::string> param, int index, float & number);
  static bool FlagToString(std::vector<std::string> param, int index, std::string &path);
  static bool FlagToPath(std::vector<std::string> param, int index, std::string &path);

private:
};
