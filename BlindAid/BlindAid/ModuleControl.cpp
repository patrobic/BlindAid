#include "ModuleControl.h"

using namespace std;
using namespace cv;

void Control::Init(Data *data, IParameters *params, IResults *input, IResults *output)
{
  _data = data;
  _params = static_cast<Parameters*>(params);
  _input = static_cast<Vision::Results*>(input);
  _output = static_cast<Results*>(output);
}

void Control::operator()()
{
}
