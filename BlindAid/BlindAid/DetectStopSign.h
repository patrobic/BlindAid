#pragma once

#include "IDetector.h"

class DetectStopSign : public IDetector
{
public:
  void Init(VisionParams *params, const cv::Mat *image, VisionResults *results);
  void Start();
  void PreProcess();
  void Process();

  void Draw();
  void Display();
  void Clear();
 
private:
  StopSignParams *_params;
  StopSignResults *_results;

};