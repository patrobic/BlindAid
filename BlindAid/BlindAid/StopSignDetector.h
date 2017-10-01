#pragma once

#include "IDetector.h"

class StopSignResults : public IDetectorResults
{
public:
  cv::Point GetPoint() { return _center; }
  int GetSize() { return _size; }

  void SetPoint(cv::Point point) { _center = point; }
  void SetSize(int size) { _size = size; }

private:
  cv::Point _center;
  int _size;
};

class StopSignDetector : public IDetector
{
public:
  void Init(const IDetectorParams *params, const cv::Mat *image, IDetectorResults *results);
  void Start();
  void PreProcess();
  void Process();

  void Draw();
  void Display();
  void Clear();
 
private:
  const StopSignParams *_params;
  StopSignResults *_results;

};