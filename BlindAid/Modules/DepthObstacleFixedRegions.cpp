#include "DepthObstacleFixedRegions.h"

using namespace std;
using namespace cv;

namespace Vision
{
  namespace DepthObstacle
  {
    namespace FixedRegions
    {
      FixedRegions::FixedRegions(IParameters *params, IData *input, IData *output) : Base(params, input, output)
      {

      }

      void FixedRegions::Process()
      {
        MaskShadows();
        SeparateRegions();
        FindMaxInRegions();
        MapVibrationValues();
      }
    }
  }
}