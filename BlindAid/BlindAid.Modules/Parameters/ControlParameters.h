#pragma once

#include "IParameters.h"

namespace Control
{
  namespace Realtime
  {
    class RealtimeControlParameters : public IParameters
    {
    public:
      RealtimeControlParameters(GlobalParameters *params) : IParameters(params)
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
    class SimulateControlParameters : public IParameters
    {
    public:
      SimulateControlParameters(GlobalParameters *params) : IParameters(params)
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

  class ControlParameters : public SwitchableParameters
  {
  public:
    enum HandPolarity { Left, Right };

    ControlParameters(GlobalParameters *params) : SwitchableParameters(params), _realtimeParams(params), _simulateParams(params)
    {
      Defaults();
    }

    void Defaults()
    {
      _realtimeParams.Defaults();
      _simulateParams.Defaults();

      _handPolarity = Right;
      _beeperIntensity = 100;
    }

    bool Valid()
    {
      return true;
    }

    Realtime::RealtimeControlParameters *GetRealtimeParams() { return &_realtimeParams; }
    Simulate::SimulateControlParameters *GetSimulateParams() { return &_simulateParams; }

    HandPolarity GetHandPolarity() { return _handPolarity; }
    void SetHandPolarity(HandPolarity handPolarity) { _handPolarity = handPolarity; }

    int GetBeeperIntensity() { return _beeperIntensity; }
    void SetBeeperIntensity(int beeperIntensity) { _beeperIntensity = beeperIntensity; }

  private:
    // realtime control parameters.
    Realtime::RealtimeControlParameters _realtimeParams;

    // simulate control parametes.
    Simulate::SimulateControlParameters _simulateParams;

    // order of the fingers.
    HandPolarity _handPolarity;

    // PWM value of the beeper.
    int _beeperIntensity;
  };
}