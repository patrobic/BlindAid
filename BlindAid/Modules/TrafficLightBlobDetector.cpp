#include "TrafficLightBlobDetector.h"

using namespace std;
using namespace cv;

namespace Vision
{
  namespace TrafficLight
  {
    namespace BlobDetector
    {
      BlobDetector::BlobDetector(IParameters *params, IData *input, IData *output) : Base(params, input, output),
        _h(_hsvChannels[0]), _s(_hsvChannels[1]), _v(_hsvChannels[2]), _b(_bgrChannels[0]), _g(_bgrChannels[1]), _r(_bgrChannels[2])
      {
        _output->SetParams(_params->GetConsecutiveCount(), _params->GetMaximumDistance(), _params->GetMaximumRadiusDiff());
      }

      void BlobDetector::Process()
      {
        MaskColors();
        DetectBlobs();
        //ConfirmWithBox();
      }

      void BlobDetector::MaskColors()
      {
        split(*_input->GetRgbImage(), _bgrChannels);
        split(*_input->GetHsvImage(), _hsvChannels);

        Mat redRegionUpper;
        Mat redRegionLower;
        inRange(*_input->GetHsvImage(), _params->GetBlobDetectorParams()->GetColorRange(0, 0), cv::Scalar(180, 255, 255), redRegionUpper);
        inRange(*_input->GetHsvImage(), cv::Scalar(0, 150, 180), _params->GetBlobDetectorParams()->GetColorRange(0, 1), redRegionLower);
        _blobMask[0] = (redRegionUpper + redRegionLower)(Rect((int)(redRegionUpper.cols * (1 - _params->GetCenterRegionRatio()) / 2), 0, (int)(redRegionUpper.rows  * _params->GetCenterRegionRatio()), (int)(redRegionUpper.rows*_params->GetUpperRegionRatio())));

        for (int i = 1; i < 3; ++i)
          inRange((*_input->GetHsvImage())(Rect(0, 0, redRegionUpper.cols, (int)(redRegionUpper.rows*_params->GetUpperRegionRatio()))), _params->GetBlobDetectorParams()->GetColorRange(i, 0), _params->GetBlobDetectorParams()->GetColorRange(i, 1), _blobMask[i]);

        //threshold(_h, _hMask, 170, 255, THRESH_TOZERO);
        //threshold(_hMask, _hMask, 190, 255, THRESH_TOZERO_INV);
        //dilate(_redMask, _redMask, Mat(), Point(-1, -1), 1);
      }

      void BlobDetector::DetectBlobs()
      {
        Ptr<SimpleBlobDetector> sbd = SimpleBlobDetector::create(*_params->GetBlobDetectorParams()->GetBlobParams());

        vector<Result> points;

        for (int i = 0; i < 3; ++i)
        {
          vector<KeyPoint> keypoints;

          sbd->detect(_blobMask[i], keypoints);

          for (int j = 0; j < keypoints.size(); j++)
          {
            points.push_back(Result(keypoints[j].pt, keypoints[j].size, (Result::Color)i));
            points.at(j)._center.x += (int)(_input->GetRgbImage()->cols * (1 - _params->GetCenterRegionRatio()) / 2);
          }
        }

        _output->Set(points);
      }

      void BlobDetector::ConfirmWithBox()
      {
        int sizeFactor = 12;
        Mat box;
        Rect rect;
        for (int color = 0; color < 3; ++color)
          for (int i = 0; i < _output->Size(); ++i)
          {
            rect.x = std::max(0, _output->At(i)._center.x - _output->Size() * sizeFactor);
            rect.y = std::max(0, _output->At(i)._center.y - _output->Size() * sizeFactor);
            rect.width = std::min(_input->GetRgbImage()->cols - rect.x - 1, _output->Size() * 2 * sizeFactor);
            rect.height = std::min(_input->GetRgbImage()->rows - rect.y - 1, _output->Size() * 2 * sizeFactor);

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