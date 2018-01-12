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
      GenerateString();
      SendControl();
      PlayAudio();

      steady_clock::time_point end = steady_clock::now();
      duration<double> time_span = duration_cast<duration<double>>(end - start);
      cout << "[CONTROL] Frame executed (" << time_span.count() * 1000 << "ms).\n";
    }

    void Realtime::SendControl()
    {
      int bytesSent = 0;

      _receivedLength = _serial.ReadData(_receivedMessage, 256);
      
      if (_receivedLength > 0)
        cout <<"[ BTRECV] " << _receivedMessage << " (" << _receivedLength << " bytes).\n";

      bytesSent = _serial.SendData(_controlMessage.c_str(), (int)_controlMessage.length());

      if (bytesSent > 0)
        cout << "[ BTSEND]" << _controlMessage << " (" << bytesSent << " bytes).\n";
    }

    void Realtime::GenerateString()
    {
      stringstream ss;

      ss << _params->GetRealtimeParams()->GetMessageStart();

      for (int i = 0; i < 5; ++i)
        ss << setw(3) << setfill('0') << (int)_vibrationIntensity[i]->Get();

      for (int i = 0; i < _params->GetOptionSignalsCount(); ++i)
        if(_params->GetOptionSignals(i) == Control::Parameters::OptionSignals::TrafficLight)
          ss << setw(3) << setfill('0') << (int)_input->GetTrafficLightResults()->GetColor();
        else if(_params->GetOptionSignals(i) == Control::Parameters::OptionSignals::NearObstacle)
          ss << setw(3) << setfill('0') << (int)_input->GetDepthObstacleResults()->GetMinRowIntensity(1);
        else
          ss << setw(3) << setfill('0') << (int)0;

      ss << _params->GetRealtimeParams()->GetMessageEnd();

      _controlMessage = ss.str();
    }

    void Realtime::PlayAudio()
    {
      if (_input->GetTrafficLightResults()->Size() > 0 && _params->GetLocalAudioEnabled())
        thread audioThread(&Realtime::TPlayAudio, this, _input->GetTrafficLightResults()->GetColor());
    }

    void Realtime::TPlayAudio(Vision::TrafficLight::Result::Color color)
    {
      if (color == Vision::TrafficLight::Result::Color::Red)
        PlaySound("Resources\\TrafficLightRed.wav", NULL, SND_FILENAME);
      else if (color == Vision::TrafficLight::Result::Color::Green)
        PlaySound("Resources\\TrafficLightGreen.wav", NULL, SND_FILENAME);
      else if (color == Vision::TrafficLight::Result::Color::Yellow)
        PlaySound("Resources\\TrafficLighYellow.wav", NULL, SND_FILENAME);
      else
        PlaySound("Resources\\TrafficLightNo.wav", NULL, SND_FILENAME);
    }
  }
}