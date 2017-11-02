#include "DetectTrafficLight.h"

using namespace std;
using namespace cv;

void DetectTrafficLight::operator()()
{
  Clear();
  Process();
}

void DetectTrafficLight::Process()
{
  PreProcess();

  switch (_params->GetMode())
  {
  case Parameters::Mode::BlobDetector:
    BlobDetectorMode();
    break;
  case Parameters::Mode::DeepLearning:
    DeepLearningMode();
    break;
  }
}

void DetectTrafficLight::PreProcess()
{
  split(*_input->GetRgbImage(), _bgrChannels);
  split(*_input->GetHsvImage(), _hsvChannels);
 
  Mat redRegionUpper;
  Mat redRegionLower;
  inRange(*_input->GetHsvImage(), cv::Scalar(150, 150, 180), cv::Scalar(180, 255, 255), redRegionUpper);
  inRange(*_input->GetHsvImage(), cv::Scalar(0, 150, 180), cv::Scalar(10, 255, 255), redRegionLower);
  _rMask = (redRegionUpper + redRegionLower)(Rect(0, 0, redRegionUpper.cols, redRegionUpper.rows*_params->GetUpperRegionToAnalyze()));

  //threshold(_h, _hMask, 170, 255, THRESH_TOZERO);
  //threshold(_hMask, _hMask, 190, 255, THRESH_TOZERO_INV);
  //dilate(_rMask, _rMask, Mat(), Point(-1, -1), 1);
}

void DetectTrafficLight::BlobDetectorMode()
{
  SimpleBlobDetector::Params params;

  params.filterByArea = true;
  params.minArea = 4 * 4;
  params.maxArea = 60 * 60;
  params.filterByCircularity = true;
  params.minCircularity = 0.1f;
  params.filterByConvexity = true;
  params.minConvexity = 0.8f;
  params.filterByInertia = true;
  params.minInertiaRatio = 0.5f;
  params.filterByColor = true;
  params.blobColor = 255;

  Ptr<SimpleBlobDetector> sbd = SimpleBlobDetector::create(params);

  vector<KeyPoint> keypoints;
  sbd->detect(_rMask, keypoints);
  
  for (int i = 0; i < keypoints.size(); i++)
    _output->PushBack(Circle(keypoints[i].pt, (int)keypoints[i].size));

  ConfirmWithBox();
}

void DetectTrafficLight::ConfirmWithBox()
{
  int sizeFactor = 12;
  Mat box;
  Rect rect;
  for (int i = 0; i < _output->Size(); ++i)
  {
    rect.x = std::max(0, _output->At(i)._center.x - _output->Size() * sizeFactor);
    rect.y = std::max(0, _output->At(i)._center.y - _output->Size() * sizeFactor);
    rect.width = std::min(_input->GetRgbImage()->cols - rect.x - 1, _output->Size() * 2 * sizeFactor);
    rect.height= std::min(_input->GetRgbImage()->rows - rect.y - 1, _output->Size() * 2 * sizeFactor);

    box = _v(rect);

    threshold(box, box, 70, 255, THRESH_BINARY_INV);
    dilate(box, box, Mat(), Point(-1, -1), 1);
    erode(box, box, Mat(), Point(-1, -1), 2);

    vector<vector<cv::Point>> contours;
    vector<Vec4i> hierarchy;

    findContours(box, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));

    vector<vector<Point> > contours_poly;
    contours_poly.resize(contours.size());


    for (int j = 0; j < contours_poly.size(); ++j)
    {
      approxPolyDP(Mat(contours[j]), contours_poly[j], 10, true);
      drawContours(box, contours_poly, j, 128, 1, 8, vector<Vec4i>(), 0, Point());
    }
    // TODO
    // detect if shape is near rectangular.
    // shape contains original light region.
  }
}

void DetectTrafficLight::DeepLearningMode()
{
  // TODO
  // integrate with deep learning API of choice.
}

void DetectTrafficLight::Clear()
{
  _output->Clear();
}