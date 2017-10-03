#include "DetectTrafficLight.h"

using namespace std;
using namespace cv;

DetectTrafficLight::DetectTrafficLight() : _h(_hsvChannels[0]), _s(_hsvChannels[1]), _v(_hsvChannels[2]), _b(_bgrChannels[0]), _g(_bgrChannels[1]), _r(_bgrChannels[2])
{

}

void DetectTrafficLight::Init(Parameters *params, const cv::Mat *image, Results *results)
{
  _params = &params->GetTrafficLightParams();
  _colorImage = image;
  _results = &results->GetTrafficLightResults();
}

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
  case TrafficLightParams::BlobDetectorMode:
    BlobDetectorApproach();
    break;
  case TrafficLightParams::HoughCirclesMode:
    HoughCirclesApproach();
    break;
  case TrafficLightParams::FindContoursMode:
    FindCountoursApproach();
    break;
  }

  DetectRectangle();
  Draw();
  Display();
}

void DetectTrafficLight::PreProcess()
{
  cvtColor(*_colorImage, _hsvImage, CV_BGR2HSV);

  split(*_colorImage, _bgrChannels);
  split(_hsvImage, _hsvChannels);
 
  Mat redRegionUpper;
  Mat redRegionLower;
  inRange(_hsvImage, cv::Scalar(150, 150, 180), cv::Scalar(180, 255, 255), redRegionUpper);
  inRange(_hsvImage, cv::Scalar(0, 150, 180), cv::Scalar(10, 255, 255), redRegionLower);
  _rMask = redRegionUpper + redRegionLower;

  //threshold(_h, _hMask, 170, 255, THRESH_TOZERO);
  //threshold(_hMask, _hMask, 190, 255, THRESH_TOZERO_INV);
  //dilate(_rMask, _rMask, Mat(), Point(-1, -1), 1);
}

void DetectTrafficLight::FindCountoursApproach()
{
  vector<vector<cv::Point>> contours;
  vector<Vec4i> hierarchy;
  double circleArea;
  double rectArea;
  vector<double> score;
  float circularityThreshold = 0.5;

  findContours(_rMask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
  
  vector<Point2f>center(contours.size());
  vector<float>radius(contours.size());

  for (int i = 0; i < contours.size(); i++)
  {
    drawContours(*_colorImage, contours, i, 255, 1, 8, vector<Vec4i>(), 0, Point());

    circleArea = contourArea(contours[i]);
    Rect rect = boundingRect(Mat(contours[i]));
    rectArea = CV_PI * ((rect.width + rect.height) ^ 2 / 4);

    score.push_back(1 - abs(circleArea - rectArea) / rectArea);

    if (score.at(i) > circularityThreshold)
    {
      minEnclosingCircle((Mat)contours[i], center[i], radius[i]);
      drawContours(*_colorImage, contours, i, 255, 1, 8, vector<Vec4i>(), 0, Point());
     
      _results->PushBack(Circle(center[i], (int)radius[i]));
    }
  }
}

void DetectTrafficLight::HoughCirclesApproach()
{
  vector<vector<cv::Point>> contours;
  vector<Vec4i> hierarchy;
  vector<cv::Vec3f> circles;

  // Option 1: Trace circle outline on mask using FindContours
  //findContours(_rMask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));

  //_rMask = Scalar::all(0);

  //for(int i = 0; i<contours.size(); ++i)
  //  drawContours(_rMask, contours, i, 255, 1, 8, vector<Vec4i>(), 0, Point());

  // Option 2: Get circle outlines by using edge detector
  int th = 100;
  Canny(_rMask, _rMask, th, th * 3);

  HoughCircles(_rMask, circles, HOUGH_GRADIENT, 1, _rMask.cols / 20, 100, 12, 1, 50);

  for (size_t i = 0; i < circles.size(); i++)
    _results->PushBack(Circle(Point(cvRound(circles[i][0]), cvRound(circles[i][1])), (int)cvRound(circles[i][2])));
}

void DetectTrafficLight::BlobDetectorApproach()
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
    _results->PushBack(Circle(keypoints[i].pt, (int)keypoints[i].size));
}

void DetectTrafficLight::DetectRectangle()
{
  int sizeFactor = 12;
  Mat box;
  Rect rect;
  for (int i = 0; i < _results->Size(); ++i)
  {
    rect.x = std::max(0, _results->At(i)._center.x - _results->Size() * sizeFactor);
    rect.y = std::max(0, _results->At(i)._center.y - _results->Size() * sizeFactor);
    rect.width = std::min(_colorImage->cols - rect.x - 1, _results->Size() * 2 * sizeFactor);
    rect.height= std::min(_colorImage->rows - rect.y - 1, _results->Size() * 2 * sizeFactor);

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

void DetectTrafficLight::Draw()
{
  for(int i = 0; i<_results->Size(); ++i)
    circle(*_colorImage, _results->At(i)._center, (int)_results->At(i)._radius + 2, Scalar(0, 255, 255), 2, 8, 0);
}

void DetectTrafficLight::Display()
{
  //namedWindow("Color");
  //moveWindow("Color", 20, 20);
  //imshow("Color", *_image);
  //namedWindow("Hue");
  //moveWindow("Hue", 1000, 20);
  //imshow("Hue", _h);
  //namedWindow("Saturation");
  //moveWindow("Saturation", 20, 600);
  //imshow("Saturation", _s);
  //namedWindow("Value");
  //moveWindow("Value", 1000, 600);
  //imshow("Value", _v);

  //waitKey();
}

void DetectTrafficLight::Clear()
{
  _results->Clear();
}