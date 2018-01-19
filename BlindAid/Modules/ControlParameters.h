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
        _serialPort = 4;
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

      }

      bool Valid()
      {
        return true;
      }

    private:

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

      _localAudioEnabled = true;
      _audioDelay = 1000;
      
      bool colors[4] = { true, false, false, false };
      for (int i = 0; i < 4; ++i) _audioColorsEnabled[i] = colors[i];

      _optionSignals[0] = TrafficLight;
      _optionSignals[1] = None;
      _optionSignalsCount = 0;
    }

    bool Valid()
    {
      return true;
    }

    Realtime::Parameters *GetRealtimeParams() { return &_realtimeParams; }
    Simulate::Parameters *GetSimulateParams() { return &_simulateParams; }

    HandPolarity GetHandPolarity() { return _handPolarity; }
    void SetHandPolarity(HandPolarity handPolarity) { _handPolarity = handPolarity; }

    bool GetLocalAudioEnabled() { return _localAudioEnabled; }
    void SetLocalAudioEnabled(bool localAudioEnabled) { _localAudioEnabled = localAudioEnabled; }

    int GetAudioDelay() { return _audioDelay; }
    void SetAudioDelay(int audioDelay) { _audioDelay = audioDelay; }

    bool GetAudioColorsEnabled(int index) { return _audioColorsEnabled[index]; }
    void SetAudioColorsEnabled(bool audioColorsEnabled, int index) { _audioColorsEnabled[index] = audioColorsEnabled; }

    OptionSignals GetOptionSignals(int i) { return _optionSignals[i]; }
    void SetOptionSignals(OptionSignals optionSignals, int i) { _optionSignals[i] = (OptionSignals)optionSignals; }

    int GetOptionSignalsCount() { return _optionSignalsCount; }
    void SetOptionSignalsCount(int optionSignalsCount) { _optionSignalsCount = optionSignalsCount; }

  private:
    // realtime control parameters.
    Realtime::Parameters _realtimeParams;

    // simulate control parametes.
    Simulate::Parameters _simulateParams;

    // order of the fingers.
    HandPolarity _handPolarity;

    // enable or disable local beeper on up board.
    bool _localAudioEnabled;

    // delay between repititions of traffic light warning.
    int _audioDelay;

    // which colors to enable warnings for.
    bool _audioColorsEnabled[4];

    // what do the last two (6th & 7th) sent signals represent.
    OptionSignals _optionSignals[2];

    // how many option signals are actually enabled.
    int _optionSignalsCount;
  };
}