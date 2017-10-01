#include "StopSignDetector.h"

using namespace cv;

void StopSignDetector::Init(const IDetectorParams *params, const cv::Mat *image, IDetectorResults *results)
{
  _params = static_cast<const StopSignParams*>(params);
  _image = image;
  _results = static_cast<StopSignResults*>(results);
}

void StopSignDetector::Start()
{


}

void StopSignDetector::PreProcess()
{
}

void StopSignDetector::Process()
{
}

void StopSignDetector::Draw()
{
}

void StopSignDetector::Display()
{
}

void StopSignDetector::Clear()
{
}



