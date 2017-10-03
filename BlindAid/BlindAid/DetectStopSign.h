#pragma once

#include "IDetector.h"

class DetectStopSign : public IDetector
{
public:
  void Init(Parameters *params, const cv::Mat *image, Results *results);
  void operator()();
  void PreProcess();
  void Process();

  void Draw();
  void Display();
  void Clear();
 
private:
  StopSignParams *_params;
  StopSignResults *_results;

};