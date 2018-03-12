#include "Main.h"

#include "MenuMain.h"

#include <iostream>
#include <windows.h>
#include <Pathcch.h>
#include <Shlwapi.h>    // For PathRemoveFileSpec()

#pragma comment(lib, "Shlwapi.lib")

using namespace std;

#ifdef _DEBUG
#define VERBOSE true
#else
#define VERBOSE false
#endif

Main::Main(std::vector<std::string> args) :
  _params(&_globalParams),
  _config(&_params),
  _results(&_params),
  _logger(_globalParams.GetLogLevel()),
  _menu(_core, &_params, &_results, &_logger, &_config)
{
  _args = args;

  Start();
}

void Main::Start()
{
  LoadSettings();
  SetExePath();
  SetWindowPosition();
  Launcher();

  if (_bypassMenu)
    Process();
  else
    _menu.ShowMenu();
}

void Main::Process()
{
  _core = new Core::Core(&_params, NULL, &_results, &_logger);

  (*_core)();
}

void Main::LoadSettings()
{
  //_config.Configure();
}

void Main::SetExePath()
{
  TCHAR path[MAX_PATH];
  int size = MAX_PATH;
  DWORD length = GetModuleFileName(NULL, path, size);
  PathRemoveFileSpec(path);

  _params.GetGlobalParameters()->SetExePath(path);
}

void Main::SetWindowPosition()
{
  HWND consoleWindow = GetConsoleWindow();
  SetWindowPos(consoleWindow, 0, _params.GetConsoleWindowPosition().x, _params.GetConsoleWindowPosition().y, (int)_params.GetConsoleWindowScale(), (int)_params.GetConsoleWindowScale(), TRUE);
}

void Main::Launcher()
{
  if (CheckFlag("-?"))
  {
    cout << "Command line argument flags to choose operation modes:\n\
        '-a': Realtime production mode (camera and glove connected).\n\
        '-c': Camera only mode (with debug messages, glove disabled).\n\
        '-‎d': Debug mode (enables extra printouts and image windows).\n\
        '-t': Control only mode (camera disabled, images loaded instead.\n\
        '-r': Record mode enabled (images and overlays saved to disk).\n\
        '-?': Help (print flags + descriptions, then exit).\n";

    system("pause");
    return;
  }
  
  if (CheckFlag("-d") || VERBOSE)
  {
    _bypassMenu = true;

    _params.GetDisplayParams()->SetToggle(SwitchableParameters::Toggle::Enabled);
    _globalParams.SetLogLevel(LogLevel::Info);
  }

  if (CheckFlag("-a"))
  {
    _bypassMenu = true;
  }
  else if (CheckFlag("-c"))
  {
    _bypassMenu = true;

    _params.GetControlParams()->SetMode(SwitchableParameters::Mode::Simulate);
    _params.SetMode(SwitchableParameters::Mode::Realtime);
  }
  else if (CheckFlag("-t"))
  {
    cout << "'-t' not implemented!\n";
    system("pause");
    return;

    _params.GetCaptureParams()->SetMode(SwitchableParameters::Mode::Simulate);
    _params.SetMode(SwitchableParameters::Mode::Realtime);
  }

  if (CheckFlag("-r"))
  {
    _params.GetRecordParams()->SetToggle(SwitchableParameters::Toggle::Enabled);
  }

  int port = 0;
  if (CheckFlag("-p", &port))
  {
    if (port != 0)
      _params.GetControlParams()->GetRealtimeParams()->SetSerialPort(port);
  }
}

bool Main::CheckFlag(const std::string& option, int *next)
{
  for (int i = 0; i < _args.size(); ++i)
    if (_args.at(i) == option)
    {
      if ((i + 1) < _args.size() && _args.at(i + 1).find_first_not_of("0123456789") == string::npos)
        *next = atoi(_args.at(i + 1).c_str());
      return true;
    }

  return false;
}

void main(int argc, char *argv[])
{
  std::vector<std::string> args(argv, argv + argc);

  Main main(args);
}