#pragma once

#include "IParameters.h"
#include "Settings.h"

#include "opencv2\core.hpp"
#include "opencv2\imgcodecs.hpp"
#include "opencv2\highgui.hpp"
#include "opencv2\imgproc.hpp"
#include "opencv2\features2d.hpp"

using namespace std;
using namespace cv;

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

class IDetectorResults
{
public:
  virtual void Clear() = 0;

protected:

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

class StopSignResults : public IDetectorResults
{
public:
  cv::Point GetPoint() { return _center; }
  int GetSize() { return _size; }

  void SetPoint(cv::Point point) { _center = point; }
  void SetSize(int size) { _size = size; }
  void Clear()
  {
    _center = cv::Point(0, 0);
    int _size = 0;
  }

private:
  cv::Point _center;
  int _size;
};

class DepthObstacleResults : public IDetectorResults
{
public:
  DepthObstacleResults()
  {
    Clear();
  }

  cv::Mat GetMat()
  {
    return _regionsMat;
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
  void Clear()
  {
    _regionsMat = cv::Mat::zeros(ROW_REGIONS, COL_REGIONS, CV_8UC1);
  }

private:
  cv::Mat _regionsMat;
};

class VisionResults
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