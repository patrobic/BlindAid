#include "StopSign.h"

using namespace std;
using namespace cv;

namespace Vision
{
  namespace StopSign
  {
    Base::Base(IParameters *params, IData *input, IData *output, Logger *logger) : IDetect(params, input, output, logger)
    {

    }

    void Base::Process()
    {

    }
  }
}