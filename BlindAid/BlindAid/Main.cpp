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
      '-d': Debug mode (enabled extra printouts and image windows).\n\
      '-t path': Control only mode (enter saved images folder path).\n\
      '-r #': Record mode enabled (enter interval in ms or 0 for manual).\n\
      '-p #': Set Bluetooth COM port index manually.\n\
      '-?': Help (print flags + descriptions, then exit).\n";

    system("pause");
    return;
  }

  if (CheckFlag("-d") || VERBOSE)
  {
    _bypassMenu = true;

    _params.GetDisplayParams()->SetToggle(SwitchableParameters::Toggle::Enabled);
    _globalParams.SetLogLevel(LogLevel::Info);

    cout << "'-d': Enabling verbose debug mode.\n";
  }

  int index = 0;
  if (CheckFlag("-a"))
  {
    _bypassMenu = true;

    cout << "'-a': Running in Realtime mode.\n";
  }
  else
  {
    if (CheckFlag("-c"))
    {
      _bypassMenu = true;

      _params.GetControlParams()->SetMode(SwitchableParameters::Mode::Simulate);
      _params.SetMode(SwitchableParameters::Mode::Realtime);

      cout << "'-c': Simulating Control to screen.\n";
    }
    if (CheckFlag("-t", &index))
    {
      string path;
      if (FlagToPath(index, &path))
      {
        _bypassMenu = true;

        _params.GetCaptureParams()->SetMode(SwitchableParameters::Mode::Simulate);
        _params.GetCaptureParams()->GetSimulateParams()->SetMediaType(Capture::Simulate::Parameters::MediaType::Sequence);
        _params.GetCaptureParams()->GetSimulateParams()->SetDepthSimDataPath(path);
        _params.GetCaptureParams()->GetSimulateParams()->SetColorSimDataPath(path);

        cout << "'-t': Simulating Capture from disk (path: '" << path << "').\n";
      }
      else
      {
        cout << "Please enter valid folder path (usage: -t C:\\Folder).\n";
        return;
      }
    }
  }

  int interval = 0;
  if (CheckFlag("-r", &interval))
  {
    if (FlagToInt(interval, &interval))
      _params.GetRecordParams()->SetInterval(interval);

    _params.GetRecordParams()->SetToggle(SwitchableParameters::Toggle::Enabled);

    cout << "'-r': Enabling recording to disk (" << interval << "ms).\n";
  }

  int port = 0;
  if (CheckFlag("-p", &port))
  {
    if (FlagToInt(port, &port))
    {
      _params.GetControlParams()->GetRealtimeParams()->SetSerialPort(port);

      cout << "'-p': COM port set to " << port << ".\n";
    }
    else
    {
      cout << "Please enter valid COM port (usage: -p #).\n";
      return;
    }
  }

  if (CheckFlag("-coloroff"))
  {
    _params.GetCaptureParams()->SetType(SwitchableParameters::Type::Depth);
    _params.GetVisionParams()->SetType(SwitchableParameters::Type::Depth);
    _params.GetControlParams()->SetType(SwitchableParameters::Type::Depth);
    _params.GetDisplayParams()->SetType(SwitchableParameters::Type::Depth);
    _params.GetRecordParams()->SetType(SwitchableParameters::Type::Depth);

    cout << "'-coloroff': Disabling color stream.\n";
  }

  if (CheckFlag("-depthoff"))
  {
    _params.GetCaptureParams()->SetType(SwitchableParameters::Type::Color);
    _params.GetVisionParams()->SetType(SwitchableParameters::Type::Color);
    _params.GetControlParams()->SetType(SwitchableParameters::Type::Color);
    _params.GetDisplayParams()->SetType(SwitchableParameters::Type::Color);
    _params.GetRecordParams()->SetType(SwitchableParameters::Type::Color);

    cout << "'-depthoff': Disabling depth stream.\n";
  }
}

bool Main::CheckFlag(const std::string& option, int *next)
{
  for (int i = 0; i < _args.size(); ++i)
    if (_args.at(i) == option)
    {
      if (next != NULL && (i + 1) < _args.size())
        *next = i + 1;
      return true;
    }

  return false;
}

bool Main::FlagToInt(int index, int *value)
{
  if (index == 0)
    return false;

  if (_args.at(index).find_first_not_of("0123456789") != string::npos)
    return false;

  *value = atoi(_args.at(index).c_str());
  return true;
}

bool Main::FlagToPath(int index, std::string *value)
{
  if (index == 0)
    return false;

  *value = _args.at(index).c_str();

  DWORD ftyp = GetFileAttributesA(value->c_str());

  if (!ftyp || !FILE_ATTRIBUTE_DIRECTORY)
    return false;

  if (PathIsDirectoryEmpty(value->c_str()))
    return false;

  return true;
}

void main(int argc, char *argv[])
{
  std::vector<std::string> args(argv, argv + argc);

  Main main(args);

  system("pause");

  return;
}