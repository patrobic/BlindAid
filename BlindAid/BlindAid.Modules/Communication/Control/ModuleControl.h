#pragma once

#include "BaseControl.h"
#include "Serial.h"

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