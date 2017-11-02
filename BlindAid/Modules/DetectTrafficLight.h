#pragma once

#include "IModule.h"
#include "ModuleCapture.h"

class DetectTrafficLight : public DetectBase
{
public:
  class Parameters : public IParameters
  {
  public:
    enum Mode
    {
      BlobDetector,
      DeepLearning
    };

    const Mode &GetMode() const { return _mode; }
    void SetMode(Mode mode) { _mode = mode; }
    
    float GetUpperRegionToAnalyze() { return _topRegionToAnalyze; }
    void SetLowerRegionToAnalyzer(float topRegionToAnalyzeR) { _topRegionToAnalyze = topRegionToAnalyzeR; }

  private:
    // detection mode to use (CV or AI).
    Mode _mode = BlobDetector;

    // upper region to inspect for traffic lights.
    float _topRegionToAnalyze = 0.5f;
  };

  class Data : public IData
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

  DetectTrafficLight(IParameters *params, IData *input, IData *output) : _h(_hsvChannels[0]), _s(_hsvChannels[1]), _v(_hsvChannels[2]), _b(_bgrChannels[0]), _g(_bgrChannels[1]), _r(_bgrChannels[2])
  {
    _params = static_cast<Parameters*>(params);
    _input = static_cast<Capture::Data*>(input);
    _output = static_cast<Data*>(output);
  }

  void operator()();
  void PreProcess();
  void Process();

  void BlobDetectorMode();
  void DeepLearningMode();
  void ConfirmWithBox();

  void Clear();

private:
  Parameters *_params;
  Capture::Data *_input;
  Data *_output;

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