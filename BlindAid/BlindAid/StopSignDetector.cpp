#include "StopSignDetector.h"

using namespace cv;

StopSignDetector::StopSignDetector(StopSignParams params)
{
  _params = params;
}

void StopSignDetector::DetectStopSign(Mat image)
{
  _rgbImage = image;
}



