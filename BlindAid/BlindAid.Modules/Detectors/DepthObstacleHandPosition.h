#pragma once

#include "DepthObstacle.h"
#include "Capture.h"

namespace Vision
{
  namespace DepthObstacle
  {
    namespace HandPosition
    {
      class HandPosition : public Base
      {
      public:
        HandPosition(IParameters * params, IData * input, IData * output, Logger *logger);
        ~HandPosition();

      private:
        void Process();
        void FindHandPosition();
      };
    }
  }
}