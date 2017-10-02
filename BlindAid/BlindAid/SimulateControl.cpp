#include "SimulateControl.h"

void ControlSim::Init(Data *data, std::thread *thread)
{
  _data = data;
  _thread = thread;
}

void ControlSim::Start()
{
  *_thread = thread(&ControlSim::TControl, this);
}

void ControlSim::SimulateOutput(int frame)
{
  cout << "[CONTROL] Frame " << to_string(frame) << " received.\n";

  resize(_depthMat, _depthMat, cv::Size(_depthMat.cols * 32, _depthMat.rows * 32), cv::INTER_NEAREST);

  namedWindow("Control Simulation");
  imshow("Control Simulation", _depthMat);
  waitKey(1);
}

void ControlSim::TControl()
{
  int frame = 0;

  do
  {
    if (_data->_newProcessedFrame)
    {
      if (_data->_resultMutex.try_lock())
      {
        frame++;

        // TODO: implement VisionResults deep copy instead.
        _data->_results.GetDepthObstacleResults().GetMat().copyTo(_depthMat);
        _data->_resultMutex.unlock();
        _data->_newProcessedFrame = false;

        SimulateOutput(frame);
      }
    }
    this_thread::sleep_for(std::chrono::milliseconds(33));
  }
  while (!_data->_visionDone || _data->_newProcessedFrame);
}
