#pragma once

#include "..\Modules\Core.h"

class SimulateMenu
{
public:
  SimulateMenu(Core::Core * core, Core::Parameters * params, Core::Data * data);
  void operator()();
  void ShowMenu();
  void Process();

private:
  void LoadFile(Capture::Simulate::Parameters::MediaType mode, std::string depthPath);
  void TestVideo(std::string colorVideoPath, std::string depthPath, int count);
  void TestPhoto(std::string colorPath, std::string depthPath, int count);

  Core::Core *_core;
  Core::Parameters *_params;
  Core::Data *_results;
};