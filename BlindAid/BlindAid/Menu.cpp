#include "Menu.h"

using namespace std;

#define PATH "C:\\Projects\\BlindAid\\TestData\\"

Menu::Menu(Core::Parameters *params, Logger *logger) : Class(params, logger),
_modes(params, logger)
{

}

bool Menu::ShowMenu()
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
      if(RealtimeMenu())
        return true;
      break;
    case '2':
      if (SimulateMenu())
        return true;
      break;
    }
    system("cls");
  } while (in != 'q' && in != 'Q');

  exit(0);
}

bool Menu::RealtimeMenu()
{
  char in;
  system("cls");

  do {
    system("cls");

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
      _modes.BypassMenu();
      return true;
    case 'c':
      _modes.CaptureOnly();
      _modes.EnableDisplay();
      return true;
    case 't':
      _modes.ControlOnly(vector<string>{ string("C:\\Record\\2018-3-12_12-39-30")});
      _modes.EnableDisplay();
      return true;
    case 's':
      _modes.SimulateMode(vector<string>{ string("C:\\Record\\2018-3-12_12-39-30")});
      _modes.EnableDisplay();
      return true;
    case 'r':
      _modes.EnableRecord(vector<string>{"0"});
      _modes.EnableDisplay();
      return true;
    }
  } while (in != 'q' && in != 'Q');

  return false;
}

bool Menu::SimulateMenu()
{
  char in;
  system("cls");

  do {
    system("cls");

    cout << "\
+========= Simulation ========+\n\
| d: Depth Obstacle Detector  |\n\
| t: Traffic Light Detector   |\n\
+=============================+\n";

    in = _getch();

    switch (in)
    {
    case 'd':
      _modes.SimulateMode(vector<string>{PATH + string("DepthObstacle")});
      _modes.DisableColor();
      _modes.EnableDisplay();
      _modes.LowPerformance();
      return true;
    case 't':
      _modes.SimulateMode(vector<string>{PATH + string("TrafficLight")});
      _modes.DisableDepth();
      _modes.EnableDisplay();
      _modes.LowPerformance();
      return true;
    }
  } while (in != 'q' && in != 'Q');

  return false;
}