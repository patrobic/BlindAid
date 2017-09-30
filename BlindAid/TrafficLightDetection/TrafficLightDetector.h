#pragma once

#include<iostream>

#include "Parameters.h"
#include "opencv2\core.hpp"
#include "opencv2\imgcodecs.hpp"
#include "opencv2\highgui.hpp"
#include "opencv2\imgproc.hpp"
#include "opencv2\features2d.hpp"

using namespace std;


struct StreetLight
{
  StreetLight(cv::Point point, float radius)
  {
    _point = point;
    _radius = radius;
  }

  cv::Point _point;
  int _radius;
};

class TrafficLightDetector
{
public:
  TrafficLightDetector(StreetLightParams params);

  void DetectTrafficLight(string path);
  void Clear();
  void Load();
  void PreProcess();
  void FindCountoursApproach();
  void HoughCirclesApproach();
  void BlobDetectorApproach();
  void DetectRectangle();
  void DrawLights();
  void Display();

private:
  StreetLightParams _params;

  string _path;
  cv::Mat _bgrImage;
  cv::Mat _hsvImage;
  cv::Mat _hsvChannels[3];
  cv::Mat _bgrChannels[3];
  cv::Mat &_h;
  cv::Mat &_s;
  cv::Mat &_v;
  cv::Mat &_r;
  cv::Mat &_g;
  cv::Mat &_b;
  cv::Mat _hMask;
  cv::Mat _rMask;
  cv::Mat _edges;

  vector<StreetLight> _streetLights;
};