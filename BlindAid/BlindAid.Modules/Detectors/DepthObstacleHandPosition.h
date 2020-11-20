#pragma once

#include "DepthObstacle.h"
#include "Capture.h"

namespace Vision
{
  namespace DepthObstacle
  {
    namespace HandPosition
    {
      class HandPosition : public DepthObstacle
      {
      public:
        HandPosition(IParameters * params, IData * input, IData * output, Tools::Logger *logger);
        ~HandPosition();

      private:
        void Process();
        void FindHandPosition();
      };
    }
  }
}