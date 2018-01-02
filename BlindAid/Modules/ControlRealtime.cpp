#include "ControlRealtime.h"

#include <iomanip>

using namespace std;
using namespace std::chrono;
using namespace cv;

namespace Control
{
  namespace Realtime
  {
    Realtime::Realtime(IParameters *params, IData *input, IData *output) : Base(params, input, output)
    {
      ConnectToArduino();
    }

    void Realtime::ConnectToArduino()
    {
      static bool connected = _serial.Open(_params->GetRealtimeParams()->GetSerialPort(), _params->GetRealtimeParams()->GetBaudRate());

      while (!connected)
      {
        cout << "connection failed!\n";

        Sleep(1000);
        connected = _serial.Open(_params->GetRealtimeParams()->GetSerialPort(), _params->GetRealtimeParams()->GetBaudRate());
      }

      cout << "connection success!\n";
    }

    void Realtime::Process()
    {
      steady_clock::time_point start = steady_clock::now();

      MapVibrationValues();
      GenerateControlString();
      CommandArduino();

      steady_clock::time_point end = steady_clock::now();
      duration<double> time_span = duration_cast<duration<double>>(end - start);
      cout << "[CONTROL] Frame executed (" << time_span.count() * 1000 << "ms).\n";
    }

    void Realtime::CommandArduino()
    {
      // TODO: make sending of data more clear/robust, and remove cout messages and use exceptions instead.
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
      stringstream ss;

      ss << _params->GetRealtimeParams()->GetMessageStart();

      for (int i = 0; i < 5; ++i)
        ss << setw(3) << setfill('0') << (int)_vibrationIntensity[i]->Get();

      for (int i = 0; i < _params->GetOptionSignalsCount(); ++i)
        ss << setw(3) << setfill('0') << (int)0; // TODO: acquire option messages from correct source, according to _optionSignals[].

      ss << _params->GetRealtimeParams()->GetMessageEnd();

      _controlMessage = ss.str();
    }
  }
}