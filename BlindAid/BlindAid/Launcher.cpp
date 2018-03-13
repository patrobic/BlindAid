#include "Launcher.h"

#include <iostream>
#include <windows.h>
#include <Pathcch.h>
#include <Shlwapi.h>

#pragma comment(lib, "Shlwapi.lib")

using namespace std;

#define NAME "Launcher"

Launcher::Launcher(Core::Core *core, Core::Parameters *params, Core::Data *data, Logger *logger, MainConfiguration *config, std::vector<std::string> args) : Menu(core, params, data, logger, config),
  _menu(core, params, data, logger, config)
{
  _args = args;
}

void Launcher::ShowMenu()
{
  LoadSettings();
  SetExePath();
  SetWindowPosition();

  if (_params->GetGlobalParameters()->GetBypassMenu())
    Process();
  else
    _menu.ShowMenu();
}

void Launcher::Process()
{
  _core = new Core::Core(_params, NULL, _results, _logger);

  (*_core)();
}

void Launcher::LoadSettings()
{
  _config->Configure(_args);
}

void Launcher::SetExePath()
{
  TCHAR path[MAX_PATH];
  int size = MAX_PATH;
  DWORD length = GetModuleFileName(NULL, path, size);
  PathRemoveFileSpec(path);

  _params->GetGlobalParameters()->SetExePath(path);
}

void Launcher::SetWindowPosition()
{
  HWND consoleWindow = GetConsoleWindow();
  SetWindowPos(consoleWindow, 0, _params->GetConsoleWindowPosition().x, _params->GetConsoleWindowPosition().y, (int)_params->GetConsoleWindowScale(), (int)_params->GetConsoleWindowScale(), TRUE);
}