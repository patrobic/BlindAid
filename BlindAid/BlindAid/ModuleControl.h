#pragma once

#include "IModule.h"

class Control : public IModule
{
public:
  void Init(Data *data);
  void operator()();

  // TODO: Implement class to control the Glove's Arduino(?) hardware once we have a working prototype.
private:

};