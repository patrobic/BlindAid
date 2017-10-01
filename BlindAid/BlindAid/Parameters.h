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

class Parameters
{
public:
  DepthObstacleParams _depthObstacleParams;
  TrafficLightParams _streetLightParams;
  StopSignParams _stopSignParams;

private:

};