#include "ControlRealtime.h"

#include <Windows.h>
#pragma comment(lib, "Winmm.lib")

using namespace std;
using namespace std::chrono;
using namespace cv;

#define NAME "CONTROL"

namespace Control
{
  namespace Realtime
  {
    Realtime::Realtime(IParameters *params, IData *input, IData *output, Logger *logger) : Base(params, input, output, logger)
    {
      if (_params->GetLocalAudioEnabled())
        _audioThread = new std::thread(&Realtime::TPlayAudio, this);

      ConnectToArduino();
    }

    void Realtime::ConnectToArduino()
    {
      LOG(Warning, "Connecting to controller (port #" + to_string(_params->GetRealtimeParams()->GetSerialPort()) + ")...", "GLOVE");
      Connect();

      while (!_serial->isConnected())
        Reconnect();

      LOG(Warning, "Connected to controller successfully", "GLOVE");
    }

    void Realtime::Connect()
    {
      _port = "\\\\.\\COM" + to_string(_params->GetRealtimeParams()->GetSerialPort());

      delete _serial;
      _serial = new SerialPort(&_port[0]);
    }

    void Realtime::Reconnect()
    {
      LOG(Warning, "Controller connection failed, attempting to reconnect (port #" + to_string(_params->GetRealtimeParams()->GetSerialPort()) + ")...", "GLOVE");
      Sleep(1000);

      Connect();
    }

    void Realtime::Process()
    {
      _start = steady_clock::now();

      GenerateString();
      SendControl();

      LOG(Info, "Control data sent to glove", _start);
    }

    void Realtime::SendControl()
    {
      int bytesSent = 0;

      //_receivedLength = _serial->readSerialPort(_receivedMessage, 256);
      //if (_receivedLength > 0)
      //  cout << "[BT-RECV] Received string = " << _receivedMessage << ".\t(" << _receivedLength << " bytes)\n";

      _sent = false;
      thread controlThread(&Realtime::TSendControl, this);
      bytesSent = _serial->writeSerialPort(_controlMessage, _messageLength);
      _sent = true;

      controlThread.join();

      if (bytesSent > 0)
        LOG(Info, "Sent message '" + string(_controlMessage) + "' (" + to_string(bytesSent * _messageLength) + " bytes)", "BT-SEND");
    }

    void Realtime::GenerateString()
    {
      stringstream ss;

      ss << _params->GetRealtimeParams()->GetMessageStart();

      for (int i = 0; i < 5; ++i)
        ss << setw(3) << setfill('0') << (int)_input->GetDepthObstacleResults()->GetVibration((_params->GetHandPolarity() == Control::Parameters::HandPolarity::Left) ? i : (4 - i))->Get();

      for (int i = 0; i < _params->GetOptionSignalsCount(); ++i)
        if (_params->GetOptionSignals(i) == Control::Parameters::OptionSignals::TrafficLight)
        {
          _input->GetTrafficLightResults()->_trafficLightMutex.lock();
          ss << setw(3) << setfill('0') << ((_input->GetTrafficLightResults()->GetColor() == Vision::TrafficLight::Result::Color::Red) ? _params->GetBeeperIntensity() : 0);
          _input->GetTrafficLightResults()->_trafficLightMutex.unlock();
        }
        else if (_params->GetOptionSignals(i) == Control::Parameters::OptionSignals::NearObstacle)
          ss << setw(3) << setfill('0') << (int)_input->GetDepthObstacleResults()->GetMaxVibration();
        else
          ss << setw(3) << setfill('0') << (int)0;

      ss << _params->GetRealtimeParams()->GetMessageEnd();

      _messageLength = (int)ss.str().length();
      for (int i = 0; i < _messageLength; ++i)
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

    void Realtime::TSendControl()
    {
      Sleep(5);
      if (_sent == false)
      {
        do Reconnect();
        while (!_serial->isConnected());

        LOG(Warning, "Connected to controller successfully", "GLOVE");
      }
    }
  }
}