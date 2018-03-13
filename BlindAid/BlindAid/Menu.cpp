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
+========== Realtime ===+\n\
| a: Production         |\n\
| c: Capture Only       |\n\
| t: Control Only       |\n\
| r: Capture + Record   |\n\
+=======================+\n";

    in = _getch();

    switch (in)
    {
    case 'a':
      _modes.RealtimeFlag();
      return true;
    case 'c':
      _modes.CaptureFlag();
      return true;
    case 't':
      _modes.ControlFlag(vector<string>{PATH + string("Sample")});
      return true;
    case 'r':
      _modes.RecordFlag(vector<string>{"0"});
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
      _modes.ControlFlag(vector<string>{PATH + string("DepthObstacle")});
      _modes.CaptureFlag();
      _modes.ColorFlag();
      _modes.DisplayFlag();
      _modes.SimulateFlag();
      return true;
    case 't':
      _modes.ControlFlag(vector<string>{PATH + string("TrafficLight")});
      _modes.CaptureFlag();
      _modes.DepthFlag();
      _modes.DisplayFlag();
      _modes.SimulateFlag();
      return true;
    }
  } while (in != 'q' && in != 'Q');

  return false;
}