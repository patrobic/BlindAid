#include "DepthObstacleHandPosition.h"

using namespace std;
using namespace cv;
using namespace std::chrono;

#define NAME "OBSTACLE"

namespace Vision
{
  namespace DepthObstacle
  {
    namespace HandPosition
    {
      HandPosition::HandPosition(IParameters *params, IData *input, IData *output, Logger *logger) : Base(params, input, output, logger)
      {

      }

      HandPosition::~HandPosition()
      {

      }

      void HandPosition::Process()
      {
        _start = steady_clock::now();

        MaskShadows();
        FindHandPosition();
        SeparateRegions();
        FindMaxInRegions();
        MapVibrationValues();
      
        LOG(Info, "Depth obstacles detected", "HANDPOS", _start);
      }

      void HandPosition::FindHandPosition()
      {
        // TODO: detect position of hand
        // use blobfinder hardcoded to expected color and size range of dot on glove, and limit to lower third of frame.

        Mat handDotMask;
        inRange(*_input->GetHsvImage(), _params->GetHandPositionParams()->GetHandDotHsvRange(0), _params->GetHandPositionParams()->GetHandDotHsvRange(1), handDotMask);

        Ptr<SimpleBlobDetector> sbd = SimpleBlobDetector::create(_params->GetHandPositionParams()->GetHandDetectorParams());

        vector<KeyPoint> keyPoints;
        sbd->detect(*_input->GetDepthImage(), keyPoints);

        if (keyPoints.size() == 0)
          _output->SetHandPosition(Point(_input->GetDepthImage()->cols / 2, _input->GetDepthImage()->rows / 2));
        else
          _output->SetHandPosition(keyPoints.at(0).pt);
      }
    }
  }
}