#include "Menu.h"

void main(int argc, char *argv[])
{
  MainMenu mainMenu;

  if (argv[1] != NULL)
  {
    std::string arg(argv[1]);

    if (arg == "-a")
    {
      mainMenu.GetParameters()->SetMode(SwitchableParameters::Mode::Realtime);
    }
    else if (arg == "-c")
    {
      mainMenu.GetParameters()->GetControlParams()->SetMode(SwitchableParameters::Mode::Simulate);
      mainMenu.GetParameters()->SetMode(SwitchableParameters::Mode::Realtime);
    }
    else if (arg == "-t")
    {
      mainMenu.GetParameters()->GetCaptureParams()->SetMode(SwitchableParameters::Mode::Simulate);
      mainMenu.GetParameters()->SetMode(SwitchableParameters::Mode::Realtime);
    }
  }

  mainMenu.GetParameters()->GetRecordParams()->SetToggle(SwitchableParameters::Toggle::Disabled);

  mainMenu();
}