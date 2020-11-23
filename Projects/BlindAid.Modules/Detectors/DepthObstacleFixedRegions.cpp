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
      FixedRegions::FixedRegions(IParameters *params, IData *input, IData *output, Tools::Logger *logger) : DepthObstacle(params, input, output, logger)
      {

      }

      FixedRegions::~FixedRegions()
      {

      }

      void FixedRegions::Process()
      {
        _start = steady_clock::now();

        FindConsecutiveMax();
        MaskShadows();
        SeparateRegions();
        FindMaxInRegions();
        MapVibrationValues();
  
        LOG(Tools::Info, "Depth obstacles detected", "FIXEDREG", _start);
      }
    }
  }
}