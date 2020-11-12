#include "TrafficLightBlobDetector.h"

using namespace std;
using namespace cv;
using namespace std::chrono;

#define NAME "TLIGHT"

namespace Vision
{
  namespace TrafficLight
  {
    namespace BlobDetector
    {
      BlobDetector::BlobDetector(IParameters *params, IData *input, IData *output, Logger *logger) : Base(params, input, output, logger),
        _h(_hsvChannels[0]), _s(_hsvChannels[1]), _v(_hsvChannels[2]), _b(_bgrChannels[0]), _g(_bgrChannels[1]), _r(_bgrChannels[2])
      {

      }

      BlobDetector::~BlobDetector()
      {

      }

      void BlobDetector::Process()
      {
        _start = steady_clock::now();
        
        CreateHsvImage();
        MaskColors();
        PreprocessImages();
        DetectBlobs();
        //ConfirmWithBox();

        LOG(Info, "Traffic lights detected", "BLOBDET", _start);
      }

      void BlobDetector::CreateHsvImage()
      {
        cvtColor(*_input->GetColorImage(), *_input->GetHsvImage(), CV_BGR2HSV);
      }

      void BlobDetector::MaskColors()
      {
        split(*_input->GetColorImage(), _bgrChannels);
        split(*_input->GetHsvImage(), _hsvChannels);

        Mat redRegionUpper;
        Mat redRegionLower;
        inRange(*_input->GetHsvImage(), _params->GetBlobDetectorParams()->GetColorRange(0, 0), cv::Scalar(180, 255, 255), redRegionUpper);
        inRange(*_input->GetHsvImage(), cv::Scalar(0, 150, 180), _params->GetBlobDetectorParams()->GetColorRange(0, 1), redRegionLower);
        _blobMask[0] = (redRegionUpper + redRegionLower)(Rect((int)(redRegionUpper.cols * (1 - _params->GetCenterRegionRatio()) / 2), 0, (int)(redRegionUpper.cols  * _params->GetCenterRegionRatio()), (int)(redRegionUpper.rows*_params->GetUpperRegionRatio())));

        for (int i = 1; i < 3; ++i)
          inRange((*_input->GetHsvImage())(Rect((int)(redRegionUpper.cols * (1 - _params->GetCenterRegionRatio()) / 2), 0, (int)(redRegionUpper.cols  * _params->GetCenterRegionRatio()), (int)(redRegionUpper.rows*_params->GetUpperRegionRatio()))), _params->GetBlobDetectorParams()->GetColorRange(i, 0), _params->GetBlobDetectorParams()->GetColorRange(i, 1), _blobMask[i]);
      }

      void BlobDetector::PreprocessImages()
      {
        //threshold(_h, _hMask, 170, 255, THRESH_TOZERO);
        //threshold(_hMask, _hMask, 190, 255, THRESH_TOZERO_INV);
        //dilate(_redMask, _redMask, Mat(), Point(-1, -1), 1);
      }

      void BlobDetector::DetectBlobs()
      {
        Ptr<SimpleBlobDetector> sbd = SimpleBlobDetector::create(*_params->GetBlobDetectorParams()->GetBlobParams());

        for (int i = 0; i < 3; ++i)
        {
          vector<KeyPoint> keypoints;
          sbd->detect(_blobMask[i], keypoints);

          for (int j = 0; j < keypoints.size(); j++)
          {
            keypoints[j].pt.x += (int)(_input->GetColorImage()->cols * (1 - _params->GetCenterRegionRatio()) / 2);
            _output->Set(Result(keypoints[j].pt, keypoints[j].size, (Result::Color)i));
          }
        }

        _output->MatchPoints();
      }

      void BlobDetector::ConfirmWithBox()
      {
        int sizeFactor = 12;
        Mat box;
        Rect rect;
        for (int color = 0; color < 3; ++color)
          for (int i = 0; i < _output->GetAll()->size(); ++i)
          {
            rect.x = std::max(0, (int)(_output->GetAll()->at(i).GetCenter().x - _output->GetAll()->size() * sizeFactor));
            rect.y = std::max(0, (int)(_output->GetAll()->at(i).GetCenter().y - _output->GetAll()->size() * sizeFactor));
            rect.width = std::min(_input->GetColorImage()->cols - rect.x - 1, (int)(_output->GetAll()->size() * 2 * sizeFactor));
            rect.height = std::min(_input->GetColorImage()->rows - rect.y - 1, (int)(_output->GetAll()->size() * 2 * sizeFactor));

            box = _v(rect);

            threshold(box, box, 70, 255, THRESH_BINARY_INV);
            dilate(box, box, Mat(), Point(-1, -1), 1);
            erode(box, box, Mat(), Point(-1, -1), 2);

            vector<vector<cv::Point>> contours;
            vector<Vec4i> hierarchy;

            findContours(box, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));

            vector<vector<Point> > contours_poly;
            contours_poly.resize(contours.size());


            for (int j = 0; j < contours_poly.size(); ++j)
            {
              approxPolyDP(Mat(contours[j]), contours_poly[j], 10, true);
              drawContours(box, contours_poly, j, 128, 1, 8, vector<Vec4i>(), 0, Point());
            }
            // TODO
            // detect if shape is near rectangular.
            // shape contains original light region.
          }
      }
    }
  }
}