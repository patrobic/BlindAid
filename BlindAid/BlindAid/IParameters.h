#pragma once

// Interface for detection module parameters.
class IDetectorParams
{
public:
  
private:

};

class DepthObstacleParams : public IDetectorParams
{
public:
  DepthObstacleParams()
  {

  }

private:

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

  TrafficLightParams()
  {
    _mode = BlobDetectorMode;
  }

  const Mode &GetMode() const { return _mode; }

  void SetMode(Mode mode) { _mode = mode; }

private:
  Mode _mode;

};

class StopSignParams : public IDetectorParams
{
public:
  StopSignParams()
  {

  }

private:

};

class VisionParams
{
public:
  DepthObstacleParams &GetDepthObstacleParams() { return _dodParams; }
  TrafficLightParams &GetTrafficLightParams() { return _sldParams; }
  StopSignParams &GetStopSignParams() { return _ssdParams; }

private:
  DepthObstacleParams _dodParams;
  TrafficLightParams _sldParams;
  StopSignParams _ssdParams;
};