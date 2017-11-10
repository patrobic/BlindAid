#pragma once

#include "IModule.h"
#include "ModuleVision.h"
#include "Serial.h"

class ControlBase : public IModule
{
public:
  class Parameters : public IParameters
  {
  public:
    enum OptionSignals
    {
      None,
      LowerUpper,
      TrafficLight
    };

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

    // TODO: any pairing options/memory once we configure BT.
  };

  class Data : public IData
  {
  public:
    void Clear() {}

  private:

  };

  ControlBase(IParameters *params, IData *input, IData *output)
  {
    _params = static_cast<Parameters*>(params);
    _input = static_cast<Vision::Data*>(input);
    _output = static_cast<Data*>(output);
  }

  virtual void operator()() = 0;

protected:
  std::string CalculateVibrationValue(int pixel) // TODO: May belong instead in Control... not ControlBase?
  {
    pixel = 255 - pixel; // TODO: implement function

    // TODO: design algorithm that calculates vibrator control value (voltage/factor/whatever is required by the API controlling the Arduino/glove).
    // Should implement a function that maps the nearest pixel intensity value to control value in some non-linear way,
    // giving higher weight to near objects (possibly negative exponential function?).
    // [intensity]
    // |.......
    // |       .....
    // |            ...
    // |               ..
    // |                 .
    // |__________________._____________ [distance]
    // 0             128             255

    return std::string(3 - std::to_string(pixel).length(), '0') + std::to_string(pixel);
  }

  void CheckConsecutiveDetections() // TODO: probably does NOT belong here.
  {
    // TODO: function that counts the number of consecutive detections of a given type (point & radius), and only accepts it once the count reaches a certain threshold.
    // Always store the detections of the previous image, along with an associated counter for each (starting at 1).
    // For each frame
    //    identify which current detections correspond to any last detections (threshold of distance and size scaling)
    //    if any do correspond
    //      overwrite previous detection with latest
    //      increment corresponding counter
    //    else
    //      delete the detection and counter
    //    for each counter-detection pair
    //       if the counter >= threshold
    //          act upon the detection (draw + feedback)

    // To do this, beef up the Results class of TrafficLight, so that each detection also includes a counter. (or should the results class be STUPID, and Control hold a copy of previous results and counter?)
    //    Where should the threshold checking be done? (TrafficLight, TrafficLight::Results, Control)???
  }

  Parameters *_params;
  Vision::Data *_input;
  Data *_output;
};

class Control : public ControlBase
{
public:
  Control(IParameters *params, IData *input, IData *output);
  void operator()();

  void CommandArduino();

private:
  void GenerateControlString();

  CSerial _serial;
  std::string _controlMessage;
  const char *_receivedMessage[256];
  int _receivedLength = 0;
};