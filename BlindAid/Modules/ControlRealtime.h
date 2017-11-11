#pragma once

#include "ControlBase.h"
#include "Serial.h"

namespace Control
{
  class Realtime : public Base
  {
  public:
    Realtime(IParameters *params, IData *input, IData *output);
    void Process();

    void CommandArduino();

  private:
    void GenerateControlString();

    CSerial _serial;
    std::string _controlMessage;
    const char *_receivedMessage[256];
    int _receivedLength = 0;
  };
}