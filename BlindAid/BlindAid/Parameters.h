#pragma once

class DepthObstacleParams
{
public:
  DepthObstacleParams()
  {

  }

private:

};

class StreetLightParams
{
public:
  StreetLightParams()
  {
    _mode = BlobDetectorMode;
  }

  enum Mode
  {
    HoughCirclesMode,
    FindContoursMode,
    BlobDetectorMode
  };

  Mode _mode;

private:

};

class StopSignParams
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
  StreetLightParams _streetLightParams;
  StopSignParams _stopSignParams;

private:

};