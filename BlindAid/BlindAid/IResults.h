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
  Region(cv::Rect rect, int intensity) { _region = rect; _intensity = intensity; }
  void Clear() { _region = cv::Rect(cv::Point(0,0), cv::Point(0, 0)); _intensity = 0; }

  cv::Rect _region;
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
  void Clear() { for (int i = 0; i < VERT_REGIONS; ++i) for (int j = 0; j < HORZ_REGIONS; ++j) _regions[i][j].Clear(); _handPosition = cv::Point(0, 0); }

  cv::Rect GetRegionBounds(int col, int row) { return _regions[col][row]._region; }
  void SetRegionBounds(int col, int row, cv::Rect region) { _regions[col][row]._region = region; }

  int GetRegionIntensity(int col, int row) { return _regions[col][row]._intensity; }
  void SetRegionIntensity(int col, int row, int intensity) { _regions[col][row]._intensity = intensity; }
  
  cv::Point GetHandPosition() { return _handPosition; }
  void SetHandPosition(cv::Point handPosition) { _handPosition = handPosition; }

  int GetMinColIntensity(int col) {
    int min = 255;
    for (int i = 0; i < HORZ_REGIONS; ++i)
      min = std::min(min, _regions[col][i]._intensity);
    return min;
  }

  int GetMinRowIntensity(int row) {
    int min = 255;
    for (int i = 0; i < HORZ_REGIONS; ++i)
      min = std::min(min, _regions[i][row]._intensity);
    return min;
  }

private:
  cv::Point _handPosition;
  std::array<std::array<Region, HORZ_REGIONS>, VERT_REGIONS> _regions;
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