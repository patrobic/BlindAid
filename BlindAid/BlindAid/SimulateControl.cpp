#include "SimulateControl.h"

void ControlSim::Init(std::thread *thread, std::mutex *resultMutex, atomic_bool *visionDone, atomic_bool *newProcessedFrame, VisionResults *results)
{
  _thread = thread;
  _visionDone = visionDone;
  _newProcessedFrame = newProcessedFrame;
  _resultMutex = resultMutex;
  _results = results;
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
    if (*_newProcessedFrame)
    {
      if (_resultMutex->try_lock())
      {
        frame++;

        // TODO: implement VisionResults deep copy instead.
        _results->GetDepthObstacleResults().GetMat().copyTo(_depthMat);
        _resultMutex->unlock();
        *_newProcessedFrame = false;

        SimulateOutput(frame);
      }
    }
    this_thread::sleep_for(std::chrono::milliseconds(33));
  }
  while (!*_visionDone || *_newProcessedFrame);
}
