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
      Realtime(IParameters *params, IData *input, IData *output);

    private:
      void Process();
      void ConnectToArduino();
      void Connect();
      void SendControl();
      void GenerateString();
      void TPlayAudio();
      void TSendControl();

      SerialPort *_serial;
      std::string _port;
      std::atomic<bool> _sent = false;
      char _controlMessage[256];
      int _messageLength = 0;
      char _receivedMessage[256];
      int _receivedLength = 0;

      std::thread *_audioThread;
      std::string _audioFiles[4] = { "TrafficLightRed.wav", "TrafficLightGreen.wav", "TrafficLighYellow.wav", "TrafficLightNo.wav" };
    };
  }
}