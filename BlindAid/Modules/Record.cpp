#include "Record.h"

using namespace std;
using namespace std::chrono;
using namespace cv;

namespace Record
{
  Record::Record(IParameters *params, IData *input, IData *output) : IModule(params, input, output)
  {
  }

  void Record::Process()
  {
    steady_clock::time_point start = steady_clock::now();

    SaveToDisk();

    steady_clock::time_point end = steady_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(end - start);

    cout << "[Record] Frame recorded (" << time_span.count() * 1000 << "ms).\n";
  }

  void Record::SaveToDisk()
  {
    // TODO: record color and depth image streams to disk
    // (sequential jpegs with unique run and frame number, or possibly video file?) photo easier and gives us ability to select image subset for testing.
    // Format: color/depth_run#_frame#.jpg, or even better create a new folder for each run.
    // Recordings/Run#/Color_Frame#.jpg, Depth_Frame#.jpg
  }
}