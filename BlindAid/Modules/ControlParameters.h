#pragma once

#include "IParameters.h"

namespace Control
{
  namespace Realtime
  {
    class Parameters : public IParameters
    {
    public:
      Parameters() { Defaults(); }

      void Defaults()
      {
        _serialPort = 2;
        _baudRate = 9600;
        _messageStart = '<';
        _messageEnd = '>';
      }

      bool Valid()
      {
        return true;
      }

      int GetSerialPort() { return _serialPort; }
      void SetSerialPort(int serialPort) { _serialPort = serialPort; }

      int GetBaudRate() { return _baudRate; }
      void SetBaudRate(int baudRate) { _baudRate = baudRate; }

      char GetMessageStart() { return _messageStart; }
      void SetMessageStart(int messageStart) { _messageStart = messageStart; }

      char GetMessageEnd() { return _messageEnd; }
      void SetMessageEnd(int messageEnd) { _messageEnd = messageEnd; }

    private:
      // COM port which bluetooth communicates.
      int _serialPort;

      // baud rate at which the COM port runs.
      int _baudRate;

      // control message start and terminating characters.
      char _messageStart;
      char _messageEnd;

      // TODO: any pairing options/memory once we configure BT.

    };
  }

  namespace Simulate
  {
    class Parameters : public IParameters
    {
    public:
      Parameters() { Defaults(); }

      void Defaults()
      {
        _vibrationWindowPosition = cv::Point(1000, 600);
        _vibrationWindowScale = 50.f;
      }

      bool Valid()
      {
        return true;
      }

      cv::Point GetVibrationWindowPosition() { return _vibrationWindowPosition; }
      void SetVibrationWindowPosition(cv::Point point) { _vibrationWindowPosition = point; }

      float GetVibrationWindowScale() { return _vibrationWindowScale; }
      void SetVibrationWindowScale(float scale) { _vibrationWindowScale = scale; }

    private:
      // position of color image window.
      cv::Point _vibrationWindowPosition;

      // scale of color image window.
      float _vibrationWindowScale;

    };
  }

  class Parameters : public SwitchableParameters
  {
  public:
    enum OptionSignals { None, LowerUpper, TrafficLight, NearObstacle };
    enum HandPolarity { Left, Right };

    Parameters() { Defaults(); }

    void Defaults()
    {
      _realtimeParams.Defaults();
      _simulateParams.Defaults();

      _handPolarity = Left;

      float bounds[HORZ_REGIONS][VERT_REGIONS] = {
         { 700, 800, 900, 800, 700 },
         { 800, 900, 1000, 900, 800 },
         { 700, 800, 900, 800, 700 } };

      for (int i = 0; i < HORZ_REGIONS; ++i)
        for (int j = 0; j < VERT_REGIONS; ++j)
          _farthestBound[i][j] = bounds[i][j];

      _nearestBound = 650;
      _minimumVibration = 0.25f;
      _maximumVibration = 255.f;
      _maximumDepthSpec = 5.f;
      _optionSignals[0] = TrafficLight;
      _optionSignals[1] = NearObstacle;
      _optionSignalsCount = 1;

      _consecutiveCount = 3;
    }

    bool Valid()
    {
      return true;
    }

    Realtime::Parameters *GetRealtimeParams() { return &_realtimeParams; }
    Simulate::Parameters *GetSimulateParams() { return &_simulateParams; }

    HandPolarity GetHandPolarity() { return _handPolarity; }
    void SetHandPolarity(HandPolarity handPolarity) { _handPolarity = handPolarity; }

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

    OptionSignals GetOptionSignals(int i) { return _optionSignals[i]; }
    void SetOptionSignals(OptionSignals optionSignals, int i) { _optionSignals[i] = (OptionSignals)optionSignals; }

    int GetOptionSignalsCount() { return _optionSignalsCount; }
    void SetOptionSignalsCount(int optionSignalsCount) { _optionSignalsCount = optionSignalsCount; }

    int GetConsecutiveCount() { return _consecutiveCount; }
    void SetConsecutiveCount(int consecutiveCount) { _consecutiveCount = consecutiveCount; }

  private:
    // realtime control parameters.
    Realtime::Parameters _realtimeParams;

    // simulate control parametes.
    Simulate::Parameters _simulateParams;

    // order of the fingers.
    HandPolarity _handPolarity;

    // farthest and nearest distance range (in meters) to consider in depth detection (zero to disable region).
    float _farthestBound[HORZ_REGIONS][VERT_REGIONS];
    float _nearestBound;

    // minimum and maximum vibration instensity ratios at farthest and nearest distances.
    float _minimumVibration;
    float _maximumVibration;

    // camera maximum depth distance (in meters), i.e. distance at pixel = 255.
    float _maximumDepthSpec;

    // what do the last two (6th & 7th) sent signals represent.
    OptionSignals _optionSignals[2];

    // how many option signals are actually enabled.
    int _optionSignalsCount;

    // number of frames for which the farthest object will be chosen.
    int _consecutiveCount;
  };
}