#pragma once

#include "IModule.h"
#include "ModuleCapture.h"

class DetectTrafficLight : public IModule
{
public:
  class Parameters : public IParameters
  {
  public:
    enum Mode
    {
      HoughCirclesMode,
      FindContoursMode,
      BlobDetectorMode
    };

    const Mode &GetMode() const { return _mode; }
    void SetMode(Mode mode) { _mode = mode; }

  private:
    Mode _mode = BlobDetectorMode;
  };

  class Results : public IResults
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

  DetectTrafficLight();

  void Init(Data *data, IParameters *params, IResults *input, IResults *output);
  void operator()();
  void PreProcess();
  void Process();

  void FindCountoursApproach();
  void HoughCirclesApproach();
  void BlobDetectorApproach();
  void DetectRectangle();

  void Clear();

private:
  Data *_data;
  Parameters *_params;
  Capture::Results *_input;
  Results *_output;

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