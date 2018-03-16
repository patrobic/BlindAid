#include "Menu.h"

using namespace std;

#define PATH "C:\\Projects\\BlindAid\\TestData\\"

Menu::Menu(Core::Parameters *params, Logger *logger) : Class(params, logger),
_modes(params, logger)
{

}

void Menu::ShowMenu()
{
  char in;
  cout << "Welcome to BlindAid!\n\n";

  do {
    cout << "\
+===== Main Menu =====+\n\
| 1: Realtime         |\n\
| 2: Simulate         |\n\
+=====================+\n";

    in = _getch();

    switch (in)
    {
    case '1':
      RealtimeMenu();
      return;
    case '2':
      SimulateMenu();
      return;
    }
    system("cls");
  } while (in != 27 && in != 'q' && in != 'Q');

  exit(0);
}

void Menu::RealtimeMenu()
{
  char in;
  system("cls");

  do {
    cout << "\
+======= Realtime ======+\n\
| a: Realtime Mode      |\n\
| c: Capture Only       |\n\
| t: Control Only       |\n\
| s: Simulate Mode      |\n\
| r: Capture + Record   |\n\
+=======================+\n";

    in = _getch();

    switch (in)
    {
    case 'a':
      return;
    case 'c':
      _modes.CaptureOnly();
      _modes.EnableDisplay();
      return;
    case 't':
      _modes.ControlOnly(vector<string>{ string(RequestUserFlag("Enter path to simulation images folder"))});
      _modes.EnableDisplay();
      return;
    case 's':
      _modes.SimulateMode(vector<string>{ string(RequestUserFlag("Enter path to simulation images folder"))});
      _modes.EnableDisplay();
      return;
    case 'r':
      _modes.EnableRecord(vector<string>{RequestUserFlag("Enter record interval (0 for manual trigger)")});
      _modes.EnableDisplay();
      return;
    }
  } while (in != 27 && in != 'q' && in != 'Q');
}

void Menu::SimulateMenu()
{
  char in;
  system("cls");

  do {
    cout << "\
+========= Simulation ========+\n\
| d: Depth Obstacle Detector  |\n\
| t: Traffic Light Detector   |\n\
+=============================+\n";

    in = _getch();

    switch (in)
    {
    case 'd':
      _modes.SimulateMode(vector<string>{RequestUserFlag("Enter path to simulation images folder")});
      _modes.DisableColor();
      _modes.EnableDisplay();
      _modes.LowPerformance();
      return;
    case 't':
      _modes.SimulateMode(vector<string>{RequestUserFlag("Enter path to simulation images folder")});
      _modes.DisableDepth();
      _modes.EnableDisplay();
      _modes.LowPerformance();
      return;
    }
  } while (in != 27 && in != 'q' && in != 'Q');
}

std::string Menu::RequestUserFlag(std::string message)
{
  std::string userInput;
  cout << message << ".\n>";
  cin >> userInput;
  return userInput;
}