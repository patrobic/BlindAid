#pragma once

#include "Class.h"

class Modes : public Class
{
public:
  Modes(Core::Parameters *params, Logger *logger);

  void HelpFlag();
  void DisplayFlag();
  void VerboseFlag();
  void RealtimeFlag();
  void CaptureFlag();
  void ControlFlag(std::vector<std::string> params);
  void RecordFlag(std::vector<std::string> params);
  void PortFlag(std::vector<std::string> params);
  void ColorFlag();
  void DepthFlag();
  void SimulateFlag();

private:
  bool FlagToInt(std::string param, int &number);
  bool FlagToString(std::string param, std::string &path);
  bool FlagToPath(std::string param, std::string &path);
};