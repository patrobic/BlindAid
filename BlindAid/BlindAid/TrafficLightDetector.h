#pragma once

#include<iostream>

#include "IDetector.h"

using namespace std;

struct Result
{
  Result(cv::Point center, int radius)
  {
    _center = center;
    _radius = radius;
  }

  cv::Point _center;
  int _radius;
};

class TrafficLightResults : public IDetectorResults
{
public:
  vector<Result>* GetResults() { return &_results; }

  void PushBack(Result &result) { _results.push_back(result); }
  int Size() { return _results.size(); }
  Result& At(int i) { return _results.at(i); }
  void Clear() { _results.clear(); }
private:
  vector<Result> _results;
};

class TrafficLightDetector : public IDetector
{
public:
  TrafficLightDetector();

  void Init(const IDetectorParams *params, const cv::Mat *image, IDetectorResults *results);
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
  const TrafficLightParams *_params;
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