#include "ModuleCapture.h"

using namespace std;
using namespace cv;

void Capture::Init(Data *data, IParameters *params, IResults *input, IResults *output)
{
  _data = data;
  _params = static_cast<Parameters*>(params);
  _input = input;
  _output = static_cast<Results*>(output);
}

void Capture::operator()()
{
}
