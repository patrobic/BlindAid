#pragma once

#include "IDetector.h"

struct NearestDistance
{
  vector<int> GetColumn(int col)
  {
    vector<int> vCol;

    for (int row = 0; row < ROW_REGIONS; ++row)
      vCol.push_back(_regions[col][row]);
    
    return vCol;
  }

  vector<int> GetRow(int row)
  {
    vector<int> hRow;

    for (int col = 0; col < COL_REGIONS; ++col)
      hRow.push_back(_regions[col][row]);

    return hRow;
  }

  int _regions[COL_REGIONS][ROW_REGIONS]; // each inner vector represents a column
};

class DetectDepthObstacle : public IDetector {
public:
  void Init(VisionParams *params, const cv::Mat *image, VisionResults *results);
  void Start();
  void Process();
  void PreProcess();

  void SeparateRegions();
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
  cv::Rect _regions[COL_REGIONS*ROW_REGIONS];
  NearestDistance _nearestDistance;

  cv::Mat _rowMax;
  cv::Mat _colMax;
  cv::Mat _rowRegion;
  cv::Mat _colRegion;
};