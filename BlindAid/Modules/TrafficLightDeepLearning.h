#pragma once

#include "TrafficLight.h"

namespace Vision
{
  namespace TrafficLight
  {
    namespace DeepLearning
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
}