#include "DepthObstacleFixedRegions.h"

using namespace std;
using namespace cv;
using namespace std::chrono;

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
        steady_clock::time_point start = steady_clock::now();

        MaskShadows();
        SeparateRegions();
        FindMaxInRegions();
        MapVibrationValues();
  
        steady_clock::time_point end = steady_clock::now();
        duration<double> time_span = duration_cast<duration<double>>(end - start);
        cout << "[OBST-FR] Depth obstacles detected.\t(" << setw(5) << (int)(time_span.count() * 1000) << " ms)\n";
      }
    }
  }
}