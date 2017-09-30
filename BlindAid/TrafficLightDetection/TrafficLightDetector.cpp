#include "TrafficLightDetector.h"

using namespace cv;

TrafficLightDetector::TrafficLightDetector(): _h(_hsvChannels[0]), _s(_hsvChannels[1]), _v(_hsvChannels[2]), _b(_bgrChannels[0]), _g(_bgrChannels[1]), _r(_bgrChannels[2])
{

}

void TrafficLightDetector::DetectTrafficLight(string path)
{
  _path = path;

  Load();
  Process();
  EdgeDetect();
  Display();
}

void TrafficLightDetector::Load()
{
  _bgrImage = cv::imread(_path);
  
  if (_bgrImage.cols == 0 || _bgrImage.rows == 0) throw("could not open image.");
  
  cvtColor(_bgrImage, _hsvImage, CV_BGR2HSV);

  split(_bgrImage, _bgrChannels);
  split(_hsvImage, _hsvChannels);

}

void TrafficLightDetector::Process()
{
  split(_bgrImage, _bgrChannels);
  split(_hsvImage, _hsvChannels);

  threshold(_h, _hMask, 170, 255, THRESH_TOZERO);
  threshold(_hMask, _hMask, 190, 255, THRESH_TOZERO_INV);
 
  Mat redRegionUpper;
  Mat redRegionLower;
  inRange(_hsvImage, cv::Scalar(150, 160, 200), cv::Scalar(180, 255, 255), redRegionUpper);
  inRange(_hsvImage, cv::Scalar(0, 160, 200), cv::Scalar(10, 255, 255), redRegionLower);
  _rMask = redRegionUpper + redRegionLower;

  vector<Vec3f> circles;
  HoughCircles(_rMask, circles, HOUGH_GRADIENT, 1, _rMask.cols / 10, 200, 10, 1, 30);

  for (size_t i = 0; i < circles.size(); i++)
  {
    Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
    int radius = cvRound(circles[i][2]);
    circle(_bgrImage, center, radius+3, Scalar(0, 255, 255), 2, LINE_4, 0);
  }
}

void TrafficLightDetector::Display()
{
  namedWindow("Color");
  moveWindow("Color", 20, 20);
  imshow("Color", _bgrImage);
  namedWindow("Hue");
  moveWindow("Hue", 1000, 20);
  imshow("Hue", _h);
  namedWindow("Saturation");
  moveWindow("Saturation", 20, 600);
  imshow("Saturation", _s);
  namedWindow("Value");
  moveWindow("Value", 1000, 600);
  imshow("Value", _v);
  
  //waitKey();
}

void TrafficLightDetector::EdgeDetect()
{
  int th = 80;
  Canny(_v, _edges, th, th * 3);
}