#include "Menu.h"

#include <windows.h>
#include <Pathcch.h>
#include <Shlwapi.h>    // For PathRemoveFileSpec()

#pragma comment(lib, "Shlwapi.lib")
using namespace std;
using namespace cv;

MainMenu::MainMenu() :
  _realtime(_core, &_params, &_results),
  _simulate(_core, &_params, &_results),
  _configuration(&_params),
  _results(&_params)
{

}

void MainMenu::operator()()
{
  Setup();
  Process();
}

void MainMenu::Setup()
{
  HWND consoleWindow = GetConsoleWindow();
  SetWindowPos(consoleWindow, 0, _params.GetConsoleWindowPosition().x, _params.GetConsoleWindowPosition().y, (int)_params.GetConsoleWindowScale(), (int)_params.GetConsoleWindowScale(), TRUE);

  TCHAR path[MAX_PATH];
  int size = MAX_PATH;
  DWORD length = GetModuleFileName(NULL, path, size);
  PathRemoveFileSpec(path);

  _params.SetExePath(path);
}

void MainMenu::Process()
{
  if (_params.GetMode() == SwitchableParameters::Mode::Realtime)
    _realtime.Process();
  else
    ShowMenu();
}

void MainMenu::ShowMenu()
{
  char in;
  cout << "Welcome to BlindAid!\n\n";

  do {
    cout << "\
+===== Main Menu =====+\n\
| 1: Realtime         |\n\
| 2: Simulate         |\n\
| 3: Reload Settings  |\n\
+=====================+\n";

    in = _getch();

    switch (in)
    {
    case '1':
      _realtime();
      break;
    case '2':
      _simulate();
      break;
    case '3':
      LoadSettings();
      break;
    }
    system("cls");
  } while (in != 'q' && in != 'Q');
}

void MainMenu::LoadSettings()
{
  _configuration.Configure();

  // TODO: user can manually specify (select and change) parameters, either via command line, or more sophisticated UI?
  // Not necessarily needed since editing the text file is just as easy...
}