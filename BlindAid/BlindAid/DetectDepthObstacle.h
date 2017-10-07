#pragma once

#include "IModule.h"
#include "ModuleCapture.h"

class DetectDepthObstacle : public DetectBase 
{
public:
  class Parameters : public IParameters
  {
  public:
    enum Mode
    {
      FingerRegions,
      HandHunting
    };

    Mode GetMode() { return _regionMode; }
    void SetMode(Mode regionMode) { _regionMode = regionMode; }

    int GetHorzRegions() { return _horzRegions; }
    void SetHorzRegions(int horzRegions) { _horzRegions = horzRegions; }

    int GetVertRegions() { return _vertRegions; }
    void SetVertRegions(int vertRegions) { _vertRegions = vertRegions; }

    float GetCenterRegionHeight() { return _centerRegionHeight; }
    void SetCenterRegionHeight(float centerRegionHeight) { _centerRegionHeight = centerRegionHeight; }

    float GetCenterRegionsWidth() { return _centerRegionsWidth; }
    void SetCenterRegionsWidth(float centerRegionsWidth) { _centerRegionsWidth = centerRegionsWidth; }

  private:
    Mode _regionMode = Mode::FingerRegions;

    int _horzRegions = HORZ_REGIONS;
    int _vertRegions = VERT_REGIONS;
    float _centerRegionHeight = 0.4f;
    float _centerRegionsWidth = 0.1f;
  };

  class Results : public IResults
  {
  public:
    Results() { Clear(); }
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

  DetectDepthObstacle(Data *data, IParameters *params, IResults *input, IResults *output)
  {
    _data = data;
    _params = static_cast<Parameters*>(params);
    _input = static_cast<Capture::Results*>(input);
    _output = static_cast<Results*>(output);
  }
  void operator()();
  void Process();
  void PreProcess();

  void DetectHand();
  void SeparateRegions();
  void SeparateRegionsEqually();
  void FindMaxInRegions();
  void FindRowMax();
  void FindColMax();
  void SplitRowRegions();
  void SplitColRegions();

  void Draw();
  void Display();
  void Clear();

private:
  Parameters *_params;
  Capture::Results *_input;
  Results *_output;

  cv::Mat _grayImage;
  cv::Mat _maskImage;
  cv::Rect _regions[HORZ_REGIONS*VERT_REGIONS];

  cv::Mat _rowMax;
  cv::Mat _colMax;
  cv::Mat _rowRegion;
  cv::Mat _colRegion;
};