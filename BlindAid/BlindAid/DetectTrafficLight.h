#pragma once

#include "IDetector.h"

class DetectTrafficLight : public IDetector
{
public:
  DetectTrafficLight();

  void Init(VisionParams *params, const cv::Mat *image, VisionResults *results);
  void Start();
  void PreProcess();
  void Process();

  void FindCountoursApproach();
  void HoughCirclesApproach();
  void BlobDetectorApproach();
  void DetectRectangle();

  void Draw();
  void Display();
  void Clear();

private:
  TrafficLightParams *_params;
  TrafficLightResults *_results;

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