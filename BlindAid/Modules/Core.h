#pragma once

#include "CoreParameters.h"
#include "CoreData.h"

namespace Core
{
  class Core : public IModule<Parameters, Data, Data>
  {
  public:
    Core(IParameters *params, IData *input, IData *output);

  private:
    void Process();
    void CreateModules();

    // capture and control declared as base class pointer so that it can be declared based on parameter as either simulate or realtime class.
    Capture::Base *_capture;
    Record::Record *_record;
    Vision::Vision *_vision;
    Control::Base *_control;
    Display::Display *_display;

    int _frame = 0;
  };
}