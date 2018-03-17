#include "Menu.h"
#include "Messages.h"

using namespace std;

#define PATH "C:\\Projects\\BlindAid\\TestData\\"

Menu::Menu(Core::Parameters *params, Logger *logger) : Class(params, logger),
_modes(params, logger)
{

}

void Menu::Configure()
{
  PrintMenu();
  GetUserInput();

  system("cls");
  return;
}

void Menu::PrintMenu()
{
  system("cls");

  cout << "Welcome to BlindAid!\n\n";
  cout << "  MAIN MENU: Enter the letter of the mode you want to select.\n";

  cout << "\n     REALTIME MODES: realistic operation modes, for final product and demo.\n\n";
  cout << "\t+====================+\n";
  for (int i = 2; i < 7; ++i)
    cout << "\t| " << Messages::messages[i][0] << ": " << setw(16) << left << Messages::messages[i][2] << "| (" << Messages::messages[i][3] << ")\n";
  cout << "\t+====================+\n";

  cout << "\n     SIMULATE MODES: testing operation modes, for testing and debugging.\n\n";
  cout << "\t+====================+\n";
  for (int i = 16; i < 18; ++i)
    cout << "\t| " << Messages::messages[i][0] << ": " << setw(16) << left << Messages::messages[i][2] << "| (" << Messages::messages[i][3] << ")\n";
  cout << "\t+====================+\n";
}

void Menu::GetUserInput()
{
  while (true)
  {
    _in = _getch();

    switch (_in)
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
    case 'o':
      _modes.SimulateMode(vector<string>{RequestUserFlag("Enter path to simulation images folder")});
      _modes.DisableColor();
      _modes.EnableDisplay();
      _modes.LowPerformance();
      _modes.SetConsecutiveCount(vector<string>{"1"});
      return;
    case 'l':
      _modes.SimulateMode(vector<string>{RequestUserFlag("Enter path to simulation images folder")});
      _modes.DisableDepth();
      _modes.EnableDisplay();
      _modes.LowPerformance();
      _modes.SetConsecutiveCount(vector<string>{"1"});
      return;
    case 'm':
      _params->GetGlobalParameters()->_args = ParseUserFlags(RequestUserFlag("Enter command line arguments, then press enter"));
      return;
    default:
      if(_in == 27 || _in == 'q' || _in == 'Q')
        exit(0);
    }
  }
}

std::string Menu::RequestUserFlag(std::string message)
{
  std::string userInput;
  cout << message << ".\n>";
  cin >> userInput;
  return userInput;
}

vector<string> Menu::ParseUserFlags(std::string message)
{
  std::vector<std::string> args;
  std::string token;
  std::istringstream stream(message);
  while (std::getline(stream, token, ' '))
    args.push_back(token);
  return args;
}