#pragma once

#include "IModule.h"
#include "Vision.h"

namespace Control
{
  class Parameters : public IParameters
  {
  public:
    enum OptionSignals
    {
      None,
      LowerUpper,
      TrafficLight
    };

    bool Valid()
    {
      return true;
    }

    int GetMaximumDistance() { return _maximumDistance; }
    void SetMaximumDistance(int maximumDistance) { _maximumDistance = maximumDistance; }

    int GetSerialPort() { return _serialPort; }
    void SetSerialPort(int serialPort) { _serialPort = serialPort; }

    int GetBaudRate() { return _baudRate; }
    void SetBaudRate(int baudRate) { _baudRate = baudRate; }

    OptionSignals GetOptionSignals() { return _optionSignals; }
    void SetOptionSignals(OptionSignals optionSignals) { _optionSignals = (OptionSignals)optionSignals; }

    float GetFarthestBound(int finger, int level) { return _farthestBound[level][finger]; }
    void SetFarthestBound(int finger, int level, float farthestBound) { _farthestBound[level][finger] = farthestBound; }

    float GetNearestBound() { return _nearestBound; }
    void SetNearestBound(float nearestBound) { _nearestBound = nearestBound; }

    float GetMinimumVibration() { return _minimumVibration; }
    void SetMinimumVibration(float minimumVibration) { _minimumVibration = minimumVibration; }

    float GetMaximumVibration() { return _maximumVibration; }
    void SetMaximumVibration(float maximumVibration) { _maximumVibration = maximumVibration; }

    float GetMaximumDepthSpec() { return _maximumDepthSpec; }
    void SetMaximumDepthSpec(float maximumDepthSpec) { _maximumDepthSpec = maximumDepthSpec; }

  private:
    // maximum distance threshold for vibrators to trigger.
    int _maximumDistance = 128;

    // COM port which bluetooth communicates.
    int _serialPort = 2;

    // baud rate at which the COM port runs.
    int _baudRate = 9600;

    // how the last two (6th & 7th) palm vibrators are used.
    OptionSignals _optionSignals = None;

    // farthest and nearest distance range (in meters) to consider in depth detection (zero to disable region).
    float _farthestBound[HORZ_REGIONS][VERT_REGIONS] = {
      { 1.5f, 2.f, 3.f, 2.f, 1.5f },
      { 2.f, 2.5f, 3.f, 2.5f, 2.f },
      { 1.5f, 2.f, 3.f, 2.f, 1.5f } };
    float _nearestBound = 0.5f;

    // minimum and maximum vibration instensity ratios at farthest and nearest distances.
    float _minimumVibration = 0.4f;
    float _maximumVibration = 1.f;
 
    // camera maximum depth distance (in meters), i.e. distance at pixel = 255.
    float _maximumDepthSpec = 5.f;

    // TODO: any pairing options/memory once we configure BT.

  };

  class Data : public IData
  {
  public:
    bool Valid()
    {
      return true;
    }

    void Clear() { } // for (int i = 0; i < VERT_REGIONS; ++i) _vibrationIntensity[i] = 0; }

    //void SetVibrationIntensity(float intensity, int col) { _vibrationIntensity[col] = intensity; }
    //float GetVibrationIntensity(int col) { return _vibrationIntensity[col]; }

  private:
    //float _vibrationIntensity[VERT_REGIONS];
  };

  class Base : public IModule<Parameters, Vision::Data, Data>
  {
  public:
    Base(IParameters *params, IData *input, IData *output);
    static Base * MakeControl(IParameters * params, IData * input, IData * output);

  protected:
    void MapVibrationValues();
    float MappingFunction(float distance, int col, int row);
    float PixelToMeters(int pixel);
    int MetersToPixel(float meters);
  
    float _vibrationIntensity[VERT_REGIONS + 2];

  };
}