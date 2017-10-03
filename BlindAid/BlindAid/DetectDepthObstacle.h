#pragma once

#include "IDetector.h"

class DetectDepthObstacle : public IDetector {
public:
  void Init(Parameters *params, const cv::Mat *image, Results *results);
  void operator()();
  void Process();
  void PreProcess();

  void DetectHand();
  void SeparateRegions();
  void SeparateRegionsEqually();
  void FindMaxInRegions();
  void FindRowMax();
  void FindColMax();
  void SplitRowRegions();
  void SplitColRegions();

  void Draw();
  void Display();
  void Clear();

private:
  DepthObstacleParams *_params;
  DepthObstacleResults *_results;

  cv::Mat _grayImage;
  cv::Mat _maskImage;
  cv::Rect _regions[HORZ_REGIONS*VERT_REGIONS];

  cv::Mat _rowMax;
  cv::Mat _colMax;
  cv::Mat _rowRegion;
  cv::Mat _colRegion;
};