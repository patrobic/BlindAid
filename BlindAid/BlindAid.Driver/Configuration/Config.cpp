#include "Config.h"

#include <windows.h>
#include <Pathcch.h>
#include <Shlwapi.h>

#pragma comment(lib, "Shlwapi.lib")

Configuration::Configuration(Core::CoreParameters *params, Tools::Logger *logger) : Class(params, logger),
_save(params, logger),
_load(params, logger),
_parse(params, logger),
_menu(params, logger)
{

}

void Configuration::Configure()
{
  Initialize();
  ParseArguments();

  if (_params->GetGlobalParameters()->GetMenuEnabled())
  {
    LoadFromMenu();
    ParseMenuArguments();
  }

  if (_params->GetGlobalParameters()->GetLoadFromDisk())
    LoadFromDisk();
}

void Configuration::LoadFromMenu()
{
  _menu.Configure();
}

void Configuration::LoadFromDisk()
{
  // TODO: implement proper file loading/validating mechanics that creates new file if nonexistant or invalid.
  // if(file exists)
  //    try(LoadConfiguration());
  //    if(!file.valid) .. LoadConfig should return if the file is valid (contains all values, and sensical)
  //      if(PromptOverwrite()) ... prompt user to overwrite existing corrupt file?
  //        Saveconfiguration();
  //      else
  //        throw exception(); ... terminate application!
  // else ... no configuration exists at all (new installation).
  //    SaveConfiguration(); ... create a file by saving the default configuration specified in each class's Parameters class.

  if (!std::ifstream(_params->GetGlobalParameters()->GetExePath() + _params->GetGlobalParameters()->_path).good())
    _save.Configure();

  _load.Configure();
}

void Configuration::ParseArguments()
{
  _parse.Configure();
}

void Configuration::ParseMenuArguments()
{
  _parse.Configure();
}

void Configuration::Initialize()
{
  SetExePath();
  SetWindowPosition();
}

void Configuration::SetExePath()
{
  TCHAR path[MAX_PATH];
  int size = MAX_PATH;
  DWORD length = GetModuleFileName(NULL, path, size);
  PathRemoveFileSpec(path);

  _params->GetGlobalParameters()->SetExePath(path);
}

void Configuration::SetWindowPosition()
{
  HWND consoleWindow = GetConsoleWindow();
  SetWindowPos(consoleWindow, 0, _params->GetConsoleWindowPosition().x, _params->GetConsoleWindowPosition().y, (int)_params->GetConsoleWindowScale(), (int)_params->GetConsoleWindowScale(), TRUE);
}