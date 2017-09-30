#pragma once

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

class Parameters
{
public:
  StreetLightParams _streetLightParams;

private:

};