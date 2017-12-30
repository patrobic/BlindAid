#include "Menu.h"

#include <windows.h>

using namespace std;
using namespace cv;

MainMenu::MainMenu():
  _realtime(_core, &_params, &_results),
  _simulate(_core, &_params, &_results),
  _configuration(&_params)
{
  
}

void MainMenu::operator()()
{
  HWND consoleWindow = GetConsoleWindow();
  SetWindowPos(consoleWindow, 0, _params.GetConsoleWindowPosition().x, _params.GetConsoleWindowPosition().y, _params.GetConsoleWindowScale(), _params.GetConsoleWindowScale(), TRUE);

  if (_params.GetMode() == SwitchableParameters::Mode::Realtime)
    Run();
  else
    ShowMenu();
}

void MainMenu::Run()
{
  _realtime.Process();
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