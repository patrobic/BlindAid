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
      ConnectToArduino();
    }

    void Realtime::Process()
    {
      _start = steady_clock::now();

      CreateMessage();
      SendControl();

      LOG(Info, "Control data sent to glove", _start);
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
      delete _serial;
      _serial = new SerialPort(string("\\\\.\\COM" + to_string(_params->GetRealtimeParams()->GetSerialPort())).c_str());
    }

    void Realtime::Reconnect()
    {
      LOG(Warning, "Controller connection failed, attempting to reconnect (port #" + to_string(_params->GetRealtimeParams()->GetSerialPort()) + ")...", "GLOVE");

      Sleep(1000);
      Connect();
    }

    void Realtime::SendControl()
    {
      int bytesSent = 0;

      _sent = false;
      thread controlThread(&Realtime::TSendControl, this);
      bytesSent = _serial->writeSerialPort(_message.str().c_str(), (int)_message.str().length());
      _sent = true;

      controlThread.join();

      if (bytesSent > 0)
        LOG(Info, "Sent message '" + string(_message.str().c_str()) + "' (" + to_string(bytesSent * _message.str().length()) + " bytes)", "BT-SEND");
    }

    void Realtime::CreateMessage()
    {
      _message.clear();
      _message << _params->GetRealtimeParams()->GetMessageStart();

      CreateColorMessage();
      CreateDepthMessage();

      _message << _params->GetRealtimeParams()->GetMessageEnd();
    }

    void Realtime::CreateColorMessage()
    {
      for (int i = 0; i < 5; ++i)
        _message << setw(3) << setfill('0') << (int)_input->GetDepthObstacleResults()->GetVibration((_params->GetHandPolarity() == Control::Parameters::HandPolarity::Left) ? i : (4 - i))->Get();
    }

    void Realtime::CreateDepthMessage()
    {
      _input->GetTrafficLightResults()->_trafficLightMutex.lock();
      _message << setw(3) << setfill('0') << ((_input->GetTrafficLightResults()->GetColor() == Vision::TrafficLight::Result::Color::Red) ? _params->GetBeeperIntensity() : 0);
      _input->GetTrafficLightResults()->_trafficLightMutex.unlock();
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