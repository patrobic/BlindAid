#pragma once

#include "IModule.h"

namespace Vision
{
  template<class Params, class Input, class Output>
  class DetectBase : public IModule<Params, Input, Output>
  {
  public:
    DetectBase(IParameters *params, IData *input, IData *output) : IModule(params, input, output)
    {

    }

  protected:

  };
}