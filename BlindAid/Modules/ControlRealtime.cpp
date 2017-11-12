#include "ControlRealtime.h"

using namespace std;
using namespace cv;

namespace Control
{
  Realtime::Realtime(IParameters *params, IData *input, IData *output) : Base(params, input, output)
  {
    static bool connected = _serial.Open(_params->GetSerialPort(), _params->GetBaudRate());

    while (!connected)
    {
      cout << "connection failed!\n";

      Sleep(1000);
      connected = _serial.Open(_params->GetSerialPort(), _params->GetBaudRate());
    }

    cout << "connection success!\n";
  }

  void Realtime::Process()
  {
    GenerateControlString();
    CommandArduino();
  }

  void Realtime::CommandArduino()
  {
    int bytesToSend = 6;
    int bytesSent = 0;

    _receivedLength = _serial.ReadData(_receivedMessage, 256);

    if (_receivedLength > 0)
      cout << "Received(" << _receivedLength << " bytes): " << _receivedMessage << endl;
    else
      cout << "Received nothing.\n";

    bytesSent = _serial.SendData(_controlMessage.c_str(), (int)_controlMessage.length());

    if (bytesSent > 0)
      cout << "Sent(" << bytesSent << " bytes): " << _controlMessage << endl;
  }

  void Realtime::GenerateControlString()
  {
    _controlMessage = "<";

    for (int i = 0; i < 5; ++i)
      _controlMessage += _vibrationIntensity[i];

    for (int i = 0; i < 2; ++i)
      _controlMessage += _vibrationIntensity[VERT_REGIONS];

    _controlMessage += ">";
  }
}