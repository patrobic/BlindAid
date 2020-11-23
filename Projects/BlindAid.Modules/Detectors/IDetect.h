#pragma once

#include "IModule.h"
#include "VisionParameters.h"

namespace Vision
{
  template<class Params, class Input, class Output>
  class IDetect : public IModule<Params, Input, Output>
  {
  public:
    IDetect(IParameters *params, IData *input, IData *output, Tools::Logger *logger) : IModule(params, input, output, logger)
    {

    }

  protected:

  };
}