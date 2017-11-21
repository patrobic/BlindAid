#include "Menu.h"

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
      Settings();
      break;
    }
    system("cls");
  } while (in != 'q' && in != 'Q');
}

void MainMenu::Settings()
{
  _configuration.Configure();

  // TODO: user can manually specify (select and change) parameters, either via command line, or more sophisticated UI?
  // Not necessarily needed since editing the text file is just as easy...
}