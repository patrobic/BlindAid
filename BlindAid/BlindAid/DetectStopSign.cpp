#include "DetectStopSign.h"

using namespace std;
using namespace cv;

void DetectStopSign::Init(Data *data, IParameters *params, IResults *input, IResults *output)
{
  _data = data;
  _params = static_cast<Parameters*>(params);
  _input = static_cast<Capture::Results*>(input);
  _output = static_cast<Results*>(output);
}

void DetectStopSign::operator()()
{


}

void DetectStopSign::PreProcess()
{
}

void DetectStopSign::Process()
{
}

void DetectStopSign::Draw()
{
}

void DetectStopSign::Display()
{
}

void DetectStopSign::Clear()
{
}



