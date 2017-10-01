#pragma once

#include "IDetector.h"

#define COL_REGIONS 5
#define ROW_REGIONS 3

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

class DepthObstacleResults : public IDetectorResults
{
public:
  DepthObstacleResults()
  {
    _regionsMat = cv::Mat::zeros(3, 5, CV_8UC1);
  }

  cv::Mat GetRowMat(int row)
  {
    return _regionsMat(cv::Rect(0, row, COL_REGIONS, 1));
  }

  cv::Mat GetColMat(int col)
  {
    return _regionsMat(cv::Rect(col, 0, 1, ROW_REGIONS));
  }

  void SetRegion(int row, int col, int value)
  {
    _regionsMat.at<char>(row, col) = value;
  }

private:
  cv::Mat _regionsMat;
};

class DepthObstacleDetector : public IDetector {
public:
  void Init(const IDetectorParams *params, const cv::Mat *image, IDetectorResults *results);
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
  const DepthObstacleParams *_params;
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