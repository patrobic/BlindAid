#include "DepthObstacleFixedRegions.h"

using namespace std;
using namespace cv;
using namespace std::chrono;

#define NAME "OBSTACLE"

namespace Vision
{
  namespace DepthObstacle
  {
    namespace FixedRegions
    {
      FixedRegions::FixedRegions(IParameters *params, IData *input, IData *output, Logger *logger) : Base(params, input, output, logger)
      {

      }

      void FixedRegions::Process()
      {
        _start = steady_clock::now();

        MaskShadows();
        SeparateRegions();
        FindMaxInRegions();
        MapVibrationValues();
  
        LOG(Info, "Depth obstacles detected", "FIXEDREG", _start);
      }
    }
  }
}