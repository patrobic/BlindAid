#include "DetectStopSign.h"

using namespace cv;

void DetectStopSign::Init(VisionParams *params, const cv::Mat *image, VisionResults *results)
{
  _params = &params->GetStopSignParams();
  _image = image;
  _results = &results->GetStopSignResults();
}

void DetectStopSign::Start()
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



