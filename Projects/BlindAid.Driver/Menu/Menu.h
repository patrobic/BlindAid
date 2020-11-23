#pragma once

#include "Modes.h"

class Menu : public Class
{
public:
  Menu(Core::CoreParameters *params, Tools::Logger *logger);
  void Configure();

private:
  void PrintMenu();
  void GetUserInput();
  std::string RequestUserFlag(std::string message);
  std::vector<std::string> ParseUserFlags(std::string message);

  Modes _modes;
  char _in;
};