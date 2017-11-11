#pragma once

#include "TrafficLightBase.h"

namespace Vision
{
  namespace TrafficLight
  {
    class DeepLearning : public Base
    {
    public:
      DeepLearning(IParameters *params, IData *input, IData *output);

    private:
      void Process();
      void RunDeepLearning();

    };
  }
}