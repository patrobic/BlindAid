#pragma once

#include "Control.h"
#include "SerialPort.h"

namespace Control
{
  namespace Realtime
  {
    class Realtime : public Base
    {
    public:
      Realtime(IParameters *params, IData *input, IData *output, Logger *logger);

    private:
      void Process();
      void ConnectToArduino();
      void Connect();
      void Reconnect();

      void SendControl();
      void CreateMessage();
      void CreateColorMessage();
      void CreateDepthMessage();
      void TPlayAudio();
      void TSendControl();

      SerialPort *_serial;
      std::atomic<bool> _sent = false;
      std::stringstream _message;

      std::thread *_audioThread;
      std::string _audioFiles[4] = { "TrafficLightRed.wav", "TrafficLightGreen.wav", "TrafficLighYellow.wav", "TrafficLightNo.wav" };
    };
  }
}