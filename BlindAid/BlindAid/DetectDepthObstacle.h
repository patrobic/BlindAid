#pragma once

#include "IModule.h"
#include "ModuleCapture.h"

#define DEPTH_RANGE 256

class DetectDepthObstacle : public DetectBase 
{
public:
  class Parameters : public IParameters
  {
  public:
    enum Mode
    {
      FingerRegions,
      HandHunting,
      HeadProtection
    };

    enum Polarity
    {
      CloseIsSmall,
      CloseIsLarge
    };

    Parameters()
    {
      _sbdParams.filterByArea = true;
      _sbdParams.minArea = 20 * 20;
      _sbdParams.maxArea = 120 * 120;
      _sbdParams.filterByCircularity = true;
      _sbdParams.minCircularity = 0.1f;
      _sbdParams.filterByConvexity = true;
      _sbdParams.minConvexity = 0.8f;
      _sbdParams.filterByInertia = true;
      _sbdParams.minInertiaRatio = 0.5f;
      _sbdParams.filterByColor = true;
      _sbdParams.blobColor = 255;
    }

    Mode GetMode() { return _regionMode; }
    void SetMode(Mode regionMode) { _regionMode = regionMode; }

    Polarity GetIntensityPolarity() { return _intensityPolarity; }
    void SetIntensityPolarity(Polarity intensityPolarity) { _intensityPolarity = intensityPolarity; }

    float GetPercentileToIgnore() { return _percentileToIgnore; }
    void SetPercentileToIgnor(float percentileToIgnore) { _percentileToIgnore = percentileToIgnore; }

    int GetHorzRegions() { return _horzRegions; }
    void SetHorzRegions(int horzRegions) { _horzRegions = horzRegions; }

    int GetVertRegions() { return _vertRegions; }
    void SetVertRegions(int vertRegions) { _vertRegions = vertRegions; }

    float GetCenterRegionHeight() { return _centerRegionHeight; }
    void SetCenterRegionHeight(float centerRegionHeight) { _centerRegionHeight = centerRegionHeight; }

    float GetCenterRegionsWidth() { return _centerRegionsWidth; }
    void SetCenterRegionsWidth(float centerRegionsWidth) { _centerRegionsWidth = centerRegionsWidth; }

    cv::Point GetDefaultHandPosition() { return _defaultHandPosition; }
    void SetDefaultHandPosition(cv::Point defaultHandPosition) { _defaultHandPosition = defaultHandPosition; }

    cv::Scalar GetHandDotHsvRange(int n) { return _handDotHsvRange[n]; }
    void SetHandDotHsvRange(int n, cv::Scalar handDotHsvRange) { _handDotHsvRange[n] = handDotHsvRange; }

    cv::SimpleBlobDetector::Params GetSbdParams() { return _sbdParams; }
    void SetSbdParams(cv::SimpleBlobDetector::Params sbdParams) { _sbdParams = sbdParams; }

  private:
    // mode used in defining region position and sizes.
    Mode _regionMode = Mode::HandHunting;

    // significance of pixel values (i.e. is distance directly or inversely proportional to pixel value).
    Polarity _intensityPolarity = Polarity::CloseIsSmall;

    // percentage of nearest pixels to ignore (to avoid false detections from noise etc.)
    float _percentileToIgnore = 0.01f;

    // number of horizontal regions to split the frame in (default is 3: upper, middle and lower).
    int _horzRegions = HORZ_REGIONS;

    // number of vertical regions to split the frame in (default is 5: one for each finger).
    int _vertRegions = VERT_REGIONS;

    // height of the central region (for hand hunting mode), other regions evenly distributed in remaining height.
    float _centerRegionHeight = 0.4f;

    // width of the central region (for hand hunting mode), other regions evenly distributed in remaining width.
    float _centerRegionsWidth = 0.1f;

    cv::Point _defaultHandPosition = cv::Point(320, 240);

    cv::Scalar _handDotHsvRange[2] = { cv::Scalar(100 / 2, 100, 100), cv::Scalar(140 / 2, 255, 255) };
    
    cv::SimpleBlobDetector::Params _sbdParams;
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

  void SetCenterPoint();
  void DetectHand();
  void SeparateRegions();
  void FindMaxInRegions();

private:
  Parameters *_params;
  Capture::Results *_input;
  Results *_output;

  cv::Mat _grayImage;
  cv::Mat _maskImage;
};