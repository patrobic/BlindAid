#pragma once

#include "DepthObstacle.h"
#include "Capture.h"

namespace Vision
{
  namespace DepthObstacle
  {
    namespace FixedRegions
    {
      class FixedRegions : public DepthObstacle
      {
      public:
        FixedRegions(IParameters * params, IData * input, IData * output, Tools::Logger *logger);
        ~FixedRegions();

      private:
        void Process();
      };
    }
  }
}