#pragma once

#include "Config.h"

class ParseConfiguration : public Configuration
{
public:
  ParseConfiguration(Core::Parameters *params, Logger *logger);
  void Configure(std::vector<std::string> args);

private:
  void HelpFlag();
  void DisplayFlag();
  void VerboseFlag();
  void RealtimeFlag();
  void CaptureFlag();
  void ControlFlag();
  void RecordFlag();
  void PortFlag();
  void ColorFlag();
  void DepthFlag();

  bool CheckFlag(const std::string & option, int *next = NULL);
  bool FlagToInt(int index, int * value);
  bool FlagToPath(int index, std::string * value);

  std::vector<std::string> _args;
};