#include "Config.h"

#include <windows.h>
#include <Pathcch.h>
#include <Shlwapi.h>

#pragma comment(lib, "Shlwapi.lib")

Configuration::Configuration(Core::Parameters *params, Logger *logger) : Class(params, logger),
  _saveConfig(params, logger),
  _loadConfig(params, logger),
  _parseConfig(params, logger)
{

}

void Configuration::Configure(std::vector<std::string> args, std::string path)
{
  _path = path;
  _args = args;

  Initialize();
  LoadFromDisk();
  ParseArguments();
}

void Configuration::ParseArguments()
{
  _parseConfig.Configure(_args);
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

  if (!std::ifstream(_params->GetGlobalParameters()->GetExePath() + _path).good())
    _saveConfig.Configure(_params->GetGlobalParameters()->GetExePath() + _path);

  _loadConfig.Configure(_params->GetGlobalParameters()->GetExePath() + _path);
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