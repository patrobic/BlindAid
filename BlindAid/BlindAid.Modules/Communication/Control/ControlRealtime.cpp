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

    Realtime::~Realtime()
    {
      delete _serial;
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
      int counter = 0;
      while (!_serial->isConnected())
      {
        Reconnect();
        if (++counter >= NUM_RETRIES)
          throw exception("Controller reconnection failed, aborting (too many retries).");
      }

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

      Sleep(RECONNECT_DELAY);
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
      _message.str("");
      _message << _params->GetRealtimeParams()->GetMessageStart();

      CreateDepthMessage();
      CreateColorMessage();

      _message << _params->GetRealtimeParams()->GetMessageEnd();
    }

    void Realtime::CreateColorMessage()
    {
      _input->GetTrafficLightResults()->_trafficLightMutex.lock();
      _message << setw(3) << setfill('0') << ((_input->GetTrafficLightResults()->GetColor() == Vision::TrafficLight::Result::Color::Red) ? _params->GetBeeperIntensity() : 0);
      _input->GetTrafficLightResults()->_trafficLightMutex.unlock();
    }

    void Realtime::CreateDepthMessage()
    {
      for (int i = 0; i < 5; ++i)
        _message << setw(3) << setfill('0') << (int)_input->GetDepthObstacleResults()->GetVibration((_params->GetHandPolarity() == Control::Parameters::HandPolarity::Left) ? i : (4 - i));
    }

    void Realtime::TSendControl()
    {
      steady_clock::time_point start = steady_clock::now();

      while (duration_cast<duration<double>>(steady_clock::now() - start).count() * 1000 < SEND_DELAY)
        if (_sent)
          return;

      int counter = 0;
      do
      {
        Reconnect();
        if (++counter >= NUM_RETRIES)
          throw exception("Controller reconnection failed, aborting (too many retries).");
      } while (!_serial->isConnected());

      LOG(Warning, "Connected to controller successfully", "GLOVE");
    }
  }
}