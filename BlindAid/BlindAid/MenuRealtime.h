#pragma once

#include "Menu.h"

class RealtimeMenu : public Menu
{
public:
  RealtimeMenu(Core::Core *core, Core::Parameters *params, Core::Data *data, Logger *logger, MainConfiguration *config);
  void ShowMenu();

private:
  void TestRealtimeComplete();
  void TestRealtimeCapture();
  void TestRealtimeControl(std::string colorPath, std::string depthPath, int count);
  void TestRecord(std::string path);
};