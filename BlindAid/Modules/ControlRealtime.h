#pragma once

#include "Control.h"
#include "Serial.h"

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
      void SendControl();
      void GenerateString();
      void PlayAudio();

      void TPlayAudio(Vision::TrafficLight::Result::Color color);

      CSerial _serial;
      std::string _controlMessage;
      const char *_receivedMessage[256];
      int _receivedLength = 0;
    };
  }
}