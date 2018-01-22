#include "ControlRealtime.h"

#include <iomanip>
#include <Windows.h>
#pragma comment(lib, "Winmm.lib")

using namespace std;
using namespace std::chrono;
using namespace cv;

namespace Control
{
  namespace Realtime
  {
    Realtime::Realtime(IParameters *params, IData *input, IData *output) : Base(params, input, output)
    {
      if(_params->GetLocalAudioEnabled())
        _audioThread = new std::thread(&Realtime::TPlayAudio, this);
   
      cout << "[  GLOVE] Connecting to controller.\n";
    }

    void Realtime::ConnectToArduino()
    {
      string port = "\\\\.\\COM" + to_string(_params->GetRealtimeParams()->GetSerialPort());
  
      _serial = new SerialPort(&port[0]);

      while (!_serial->isConnected())
      {
        cout << "[  GLOVE] Connection failed, attempting to reconnect (port #" << _params->GetRealtimeParams()->GetSerialPort() << ").\n";
        Sleep(1000);

        delete _serial;
        _serial = new SerialPort(&port[0]);
      }

      cout << "[  GLOVE] Connection success!\n";
    }

    void Realtime::Process()
    {
      steady_clock::time_point start = steady_clock::now();

      ConnectToArduino();
      GenerateString();
      SendControl();

      steady_clock::time_point end = steady_clock::now();
      duration<double> time_span = duration_cast<duration<double>>(end - start);
      cout << "[CONTROL] Frame executed (" << time_span.count() * 1000 << "ms).\n";
    }

    void Realtime::SendControl()
    {
      int bytesSent = 0;

      _receivedLength = _serial->readSerialPort(_receivedMessage, 256);

      if (_receivedLength > 0)
        cout << "[ BTRECV] " << _receivedMessage << " (" << _receivedLength << " bytes).\n";

      bytesSent = _serial->writeSerialPort(_controlMessage, _messageLength);

      if (bytesSent > 0)
        cout << "[ BTSEND]" << _controlMessage << " (" << bytesSent << " bytes).\n";
    }

    void Realtime::GenerateString()
    {
      stringstream ss;

      ss << _params->GetRealtimeParams()->GetMessageStart();

      for (int i = 0; i < 5; ++i)
        ss << setw(3) << setfill('0') << (int)_input->GetDepthObstacleResults()->GetVibration(i)->Get();

      for (int i = 0; i < _params->GetOptionSignalsCount(); ++i)
        if (_params->GetOptionSignals(i) == Control::Parameters::OptionSignals::TrafficLight)
          ss << setw(3) << setfill('0') << (int)_input->GetTrafficLightResults()->GetColor();
        else if (_params->GetOptionSignals(i) == Control::Parameters::OptionSignals::NearObstacle)
          ss << setw(3) << setfill('0') << (int)_input->GetDepthObstacleResults()->GetMaxVibration();
        else
          ss << setw(3) << setfill('0') << (int)0;

      ss << _params->GetRealtimeParams()->GetMessageEnd();

      _messageLength = (int)ss.str().length();
      for(int i = 0; i < _messageLength; ++i)
        _controlMessage[i] = ss.str().at(i);
    }

    void Realtime::TPlayAudio()
    {
      while (true)
      {
        for (int i = 0; i < 4; ++i)
          if (_input->GetTrafficLightResults()->GetColor() == (Vision::TrafficLight::Result::Color)i && _params->GetAudioColorsEnabled(i))
            PlaySound(_audioFiles[i].c_str(), NULL, SND_FILENAME);

        Sleep(_params->GetAudioDelay());
      }
    }
  }
}