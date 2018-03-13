#pragma once

#include "Class.h"
#include "Modes.h"

class ParseConfiguration : public Class
{
public:
  ParseConfiguration(Core::Parameters *params, Logger *logger);
  void Configure(std::vector<std::string> args);

private:
  bool CheckFlag(const std::string & option, int numParams = 0);

  std::vector<std::string> _args;
  std::vector<std::string> _prms;

  int _index = 0;
  Modes _modes;
};