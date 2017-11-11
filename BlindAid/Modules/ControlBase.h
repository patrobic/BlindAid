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

  private:
    // maximum distance threshold for vibrators to trigger.
    int _maximumDistance = 128;

    // COM port which bluetooth communicates.
    int _serialPort = 2;

    // baud rate at which the COM port runs.
    int _baudRate = 9600;

    // how the last two (6th & 7th) palm vibrators are used.
    OptionSignals _optionSignals = None;

    // TODO: add weighting factors for various fingers and image heights.


    // TODO: any pairing options/memory once we configure BT.

  };

  class Data : public IData
  {
  public:
    bool Valid()
    {
      return true;
    }

    void Clear() {}

  private:

  };

  class Base : public IModule<Parameters, Vision::Data, Data>
  {
  public:
    Base(IParameters *params, IData *input, IData *output);
    static Base * MakeControl(IParameters * params, IData * input, IData * output);

  protected:
    std::string CalculateVibrationValue(int pixel);
    void CheckConsecutiveDetections();
  };
}