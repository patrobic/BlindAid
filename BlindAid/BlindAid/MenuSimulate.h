#pragma once

#include "Menu.h"

class SimulateMenu : public Menu
{
public:
  SimulateMenu(Core::Core *core, Core::Parameters *params, Core::Data *data, Logger *logger);
  void ShowMenu();

private:
  void SetParameters();
  void LoadFile(Capture::Simulate::Parameters::MediaType mode, std::string depthPath);
  void TestVideo(std::string colorVideoPath, std::string depthPath, int count);
  void TestPhoto(std::string colorPath, std::string depthPath, int count);
  void TestSequence();
};