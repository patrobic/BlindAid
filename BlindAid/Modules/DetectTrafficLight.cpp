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
  inRange(*_input->GetHsvImage(), _params->GetColorRange(0, 0), cv::Scalar(180, 255, 255), redRegionUpper);
  inRange(*_input->GetHsvImage(), cv::Scalar(0, 150, 180), _params->GetColorRange(0, 1), redRegionLower);
  _blobMask[0] = (redRegionUpper + redRegionLower)(Rect(0, 0, redRegionUpper.cols, redRegionUpper.rows*_params->GetUpperRegionToAnalyze()));

  for(int i = 1; i < 3; ++i)
    inRange((*_input->GetHsvImage())(Rect(0, 0, redRegionUpper.cols, redRegionUpper.rows*_params->GetUpperRegionToAnalyze())), _params->GetColorRange(i, 0), _params->GetColorRange(i, 1), _blobMask[i]);

  //threshold(_h, _hMask, 170, 255, THRESH_TOZERO);
  //threshold(_hMask, _hMask, 190, 255, THRESH_TOZERO_INV);
  //dilate(_redMask, _redMask, Mat(), Point(-1, -1), 1);
}

void DetectTrafficLight::BlobDetectorMode()
{
  Ptr<SimpleBlobDetector> sbd = SimpleBlobDetector::create(*_params->GetBlobParams());

  vector<KeyPoint> keypoints;

  for (int i = 0; i < 3; ++i)
  {
    vector<KeyPoint> keypoints;

    sbd->detect(_blobMask[i], keypoints);

    for (int j = 0; j < keypoints.size(); j++)
      _output->PushBack(Circle(keypoints[j].pt, (int)keypoints[j].size, (Circle::Color)i));
  }

  //ConfirmWithBox();
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