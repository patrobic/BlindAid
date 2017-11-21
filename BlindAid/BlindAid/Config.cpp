#include "Config.h"

Configuration::Configuration(Core::Parameters *params) :
  _saveConfig(params, CONFIG_FILE),
  _loadConfig(params, CONFIG_FILE)
{

}

void Configuration::Configure()
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

  if (std::ifstream(CONFIG_FILE))
    _saveConfig();

  _loadConfig();
}