#pragma once

#include "ControlBase.h"
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
      void CommandArduino();
      void GenerateControlString();

      CSerial _serial;
      std::string _controlMessage;
      const char *_receivedMessage[256];
      int _receivedLength = 0;
    };
  }
}