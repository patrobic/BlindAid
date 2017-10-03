#include "SimulateControl.h"

using namespace std;
using namespace cv;

void ControlSim::Init(Data *data)
{
  _data = data;
}

void ControlSim::operator()()
{
  _data->_controlThread = thread(&ControlSim::ControlThread, this);
}

void ControlSim::SimulateOutput(int frame)
{
  cout << "[CONTROL] Frame " << to_string(frame) << " received.\n";

  resize(_depthMat, _depthMat, cv::Size(_depthMat.cols * 32, _depthMat.rows * 32), cv::INTER_NEAREST);

  namedWindow("Control Simulation");
  imshow("Control Simulation", _depthMat);
  waitKey(1);
}

void ControlSim::ControlThread()
{
  int frame = 0;

  do
  {
    if (_data->_newFrameForControl)
    {
      if (_data->_resultMutex.try_lock())
      {
        frame++;

        // TODO: implement VisionResults deep copy instead.
        _data->_results.GetDepthObstacleResults().GetMat().copyTo(_depthMat);
        _data->_resultMutex.unlock();
        _data->_newFrameForControl = false;

        SimulateOutput(frame);
      }
    }
    this_thread::sleep_for(chrono::milliseconds(33));
  }
  while (!_data->_visionDone || _data->_newFrameForControl);
}
