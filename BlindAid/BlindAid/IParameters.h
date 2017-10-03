#pragma once

#define HORZ_REGIONS 3
#define VERT_REGIONS 5

// Interface for detection module parameters.
class IDetectorParams
{
public:
  
private:
};

class DepthObstacleParams : public IDetectorParams
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
  Mode _regionMode = Mode::HandHunting;

  int _horzRegions = HORZ_REGIONS;
  int _vertRegions = VERT_REGIONS;
  float _centerRegionHeight = 0.4f;
  float _centerRegionsWidth = 0.1f;
};

class TrafficLightParams : public IDetectorParams
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

struct StopSignParams : public IDetectorParams
{
public:

private:
};

class Parameters
{
public:
  enum Mode
  {
    Simulate,
    Realtime
  };
  enum MediaType
  {
    Photo,
    Video
  };

  Mode GetCaptureMode() { return _captureMode; }
  void SetCaptureMode(Mode captureMode) { _captureMode = captureMode; }
  Mode GetControlMode() { return _controlMode; }
  void SetControlMode(Mode controlMode) { _controlMode = controlMode; }

  MediaType GetMediaType() { return _mediaType; }
  void SetMediaType(MediaType mediaType) { _mediaType = mediaType; }

  std::string GetColorSimDataPath() { return _colorSimDataPath; }
  void SetColorSimDataPath(std::string colorSimDataPath) { _colorSimDataPath = colorSimDataPath; }
  std::string GetDepthSimDataPath() { return _depthSimDataPath; }
  void SetDepthSimDataPath(std::string depthSimDataPath) { _depthSimDataPath = depthSimDataPath; }

  bool GetEnableDisplay() { return _enableDisplay; }
  void SetEnableDisplay(bool enableDisplay) { _enableDisplay = enableDisplay; }

  DepthObstacleParams &GetDepthObstacleParams() { return _dodParams; }
  TrafficLightParams &GetTrafficLightParams() { return _sldParams; }
  StopSignParams &GetStopSignParams() { return _ssdParams; }

private:
  Mode _captureMode = Realtime;
  Mode _controlMode = Realtime;

  MediaType _mediaType = Photo;
  std::string _colorSimDataPath;
  std::string _depthSimDataPath;

  bool _enableDisplay = false;

  DepthObstacleParams _dodParams;
  TrafficLightParams _sldParams;
  StopSignParams _ssdParams;
};