#include "SimulateCapture.h"

using namespace std;
using namespace std::chrono;
using namespace cv;

void CaptureSim::Init(Data *data, IParameters *params, IResults *input, IResults *output)
{
  _data = data;
  _params = static_cast<Parameters*>(params);
  _input = input;
  _output = static_cast<Results*>(output);
}

void CaptureSim::operator()()
{
  _data->_captureDone = false;

  if (_params->GetMediaType())
  {
    _cap.open(_params->GetColorSimDataPath());
    _data->_captureThread = thread(&CaptureSim::VideoCaptureThread, this);
  }
  else
  {
    _data->_captureThread = thread(&CaptureSim::PhotoCaptureThread, this);
  }
}

void CaptureSim::VideoCaptureThread()
{
  int frame = 0;
  *_output->GetDepthImage() = imread(_params->GetDepthSimDataPath());

  do 
  {
    frame++;

    steady_clock::time_point start = steady_clock::now();
    _data->_bufferMutex.lock();
    _data->_captureDone = !_cap.read(*_output->GetColorImage());
    _data->_bufferMutex.unlock();
    steady_clock::time_point end = steady_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(end - start);

    _data->_newFrameForVision = true;

    cout << "[CAPTURESIM] Frame " << to_string(frame) << " load time : " << time_span.count() * 1000 << "ms.\n";
    this_thread::sleep_for(milliseconds(33));
  }
  while (!_data->_captureDone);

  _data->_captureDone = true;
}

void CaptureSim::PhotoCaptureThread()
{
  _data->_bufferMutex.lock();

  *_output->GetColorImage() = imread(_params->GetColorSimDataPath());
  *_output->GetDepthImage() = imread(_params->GetDepthSimDataPath());
  if (_output->GetColorImage()->cols == 0 || _output->GetColorImage()->rows == 0) throw("could not open image.");

  _data->_bufferMutex.unlock();
  _data->_newFrameForVision = true;

  cout << "[CAPTURESIM] Photo loaded.\n";
  _data->_captureDone = true;
}