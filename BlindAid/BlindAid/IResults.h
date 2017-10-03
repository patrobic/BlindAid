#pragma once

#include <array>

#include "opencv2\core.hpp"
#include "IParameters.h"

class IDetectorResults
{
public:
  virtual void Clear() = 0;

protected:

};

struct Circle
{
  Circle() {}
  Circle(cv::Point center, int radius) { _center = center; _radius = radius; }
  void Clear() { _center = cv::Point(0, 0); _radius = 0; }

  cv::Point _center;
  int _radius;
};

struct Region
{
  Region() {}
  Region(cv::Rect rect, int intensity) { _rect = rect; _intensity = intensity; }

  cv::Rect _rect;
  int _intensity;
};

class TrafficLightResults : public IDetectorResults
{
public:
  void Clear() { _results.clear(); }

  std::vector<Circle>* GetRegions() { return &_results; }
  void PushBack(Circle &result) { _results.push_back(result); }
  int Size() { return (int)_results.size(); }
  Circle& At(int i) { return _results.at(i); }

private:
  std::vector<Circle> _results;
};

class StopSignResults : public IDetectorResults
{
public:
  void Clear() { _circle.Clear(); }

  Circle GetRegion() { return _circle; }
  void SetRegion(Circle circle) { _circle = circle; }

private:
  Circle _circle;
};

class DepthObstacleResults : public IDetectorResults
{
public:
  DepthObstacleResults() { Clear(); }

  cv::Mat GetMat() { return _regionsMat; }
  cv::Mat GetRowMat(int row) { return _regionsMat.row(row); }
  cv::Mat GetColMat(int col) { return _regionsMat.col(col); }

  void SetRegion(int row, int col, int value) { _regionsMat.at<char>(row, col) = value; }
  void Clear() { _regionsMat = cv::Mat::zeros(HORZ_REGIONS, VERT_REGIONS, CV_8UC1); }
  
private:
  cv::Mat _regionsMat;
  cv::Point _handPosition;

  // TODO: switch from MAT to 2D array, also storing Rect in depthImage.
  std::array<std::array<int, 3>, 5> _regions;
};

class Results
{
public:
  TrafficLightResults &GetTrafficLightResults() { return _tldResults; }
  StopSignResults &GetStopSignResults() { return _ssdResults; }
  DepthObstacleResults &GetDepthObstacleResults() { return _dodResults; }

private:
  TrafficLightResults _tldResults;
  StopSignResults _ssdResults;
  DepthObstacleResults _dodResults;
};