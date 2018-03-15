#pragma once

#include "IParameters.h"

namespace Control
{
  namespace Realtime
  {
    class Parameters : public IParameters
    {
    public:
      Parameters(GlobalParameters *params) : IParameters(params)
      {
        Defaults();
      }

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
    };
  }

  namespace Simulate
  {
    class Parameters : public IParameters
    {
    public:
      Parameters(GlobalParameters *params) : IParameters(params)
      {
        Defaults();
      }

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
    enum HandPolarity { Left, Right };

    Parameters(GlobalParameters *params) : SwitchableParameters(params), _realtimeParams(params), _simulateParams(params)
    {
      Defaults();
    }

    void Defaults()
    {
      _realtimeParams.Defaults();
      _simulateParams.Defaults();

      _handPolarity = Right;
      _beeperIntensity = 150;
    }

    bool Valid()
    {
      return true;
    }

    Realtime::Parameters *GetRealtimeParams() { return &_realtimeParams; }
    Simulate::Parameters *GetSimulateParams() { return &_simulateParams; }

    HandPolarity GetHandPolarity() { return _handPolarity; }
    void SetHandPolarity(HandPolarity handPolarity) { _handPolarity = handPolarity; }

    int GetBeeperIntensity() { return _beeperIntensity; }
    void SetBeeperIntensity(int beeperIntensity) { _beeperIntensity = beeperIntensity; }

  private:
    // realtime control parameters.
    Realtime::Parameters _realtimeParams;

    // simulate control parametes.
    Simulate::Parameters _simulateParams;

    // order of the fingers.
    HandPolarity _handPolarity;

    // PWM value of the beeper.
    int _beeperIntensity;
  };
}