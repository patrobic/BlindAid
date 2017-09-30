#pragma once

#include<iostream>

#include "opencv2\core.hpp"
#include "opencv2\imgcodecs.hpp"
#include "opencv2\highgui.hpp"
#include "opencv2\imgproc.hpp"

using namespace std;

class TrafficLightDetector
{
public:
  TrafficLightDetector();

  void DetectTrafficLight(string path);
  void Load();
  void Process();
  void EdgeDetect();
  void Display();

private:
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
};