#include "Menu.h"

using namespace std;
using namespace cv;

MainMenu::MainMenu():
  _realtime(_core, &_params, &_results),
  _simulate(_core, &_params, &_results)
{
  Configure();
}

void MainMenu::operator()()
{
  ShowMenu();
}

void MainMenu::Configure()
{
  // TODO: implement proper file loading/validating mechanics that creates new file if nonexistant or invalid.
  // if(file exists)
  //    try(LoadConfiguration());
  //    if(!file.valid) .. LoadConfig should return if the file is valid (contains all values, and sensical)
  //      if(PromptOverwrite()) ... prompt user to overwrite existing corrupt file?
  //        Saveconfiguration();
  //      else
  //        throw exception(); ... terminate application!
  // else ... no configuration exists at all (new installation).
  //    SaveConfiguration(); ... create a file by saving the default configuration specified in each class's Parameters class.

  SaveConfiguration saveConfig(&_params, "BlindAid.cfg");
  saveConfig();

  LoadConfiguration loadConfig(&_params, "BlindAid.cfg");
  loadConfig();

  _params.GetRecordParams()->SetToggle(SwitchableParameters::Toggle::Disabled);
}

void MainMenu::ShowMenu()
{
  char in;
  cout << "Welcome to BlindAid!\n\n";

  do {
    cout << "\
+== Main Menu ==+\n\
| 1: Realtime   |\n\
| 2: Simulate   |\n\
| 3: Settings   |\n\
+===============+\n";

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
  // TODO: user can manually specify (select and change) parameters, either via command line, or more sophisticated UI?
  // Not necessarily needed since editing the text file is just as easy...
}