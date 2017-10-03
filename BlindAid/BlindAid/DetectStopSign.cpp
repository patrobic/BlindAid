#include "DetectStopSign.h"

using namespace std;
using namespace cv;

void DetectStopSign::Init(Parameters *params, const cv::Mat *image, Results *results)
{
  _params = &params->GetStopSignParams();
  _colorImage = image;
  _results = &results->GetStopSignResults();
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



