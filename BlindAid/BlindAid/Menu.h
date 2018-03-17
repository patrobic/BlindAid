#pragma once

#include "Modes.h"

class Menu : public Class
{
public:
  Menu(Core::Parameters *params, Logger *logger);
  void Configure();

private:
  void PrintMenu();
  std::string RequestUserFlag(std::string message);
  std::vector<std::string> ParseUserFlags(std::string message);

  Modes _modes;
};