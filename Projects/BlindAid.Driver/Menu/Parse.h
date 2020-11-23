#pragma once

#include "Class.h"
#include "Modes.h"

class Parse : public Class
{
public:
  Parse(Core::CoreParameters *params, Tools::Logger *logger);
  void Configure();

private:
  bool CheckFlag(const std::string & option, int numParams = 0);

  Modes _modes;
  std::vector<std::string> _prms;
  int _index = 0;
};