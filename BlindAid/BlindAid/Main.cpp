#include "Menu.h"

void main(int argc, char *argv[])
{
  MainMenu mainMenu;

  if (argv[1] != NULL && std::string(argv[1]) == "-a")
    mainMenu.GetParameters()->SetMode(SwitchableParameters::Mode::Realtime);

  mainMenu();
}