#include "DetectDepthObstacle.h"

using namespace std;
using namespace cv;

void DetectDepthObstacle::Init(Parameters *params, const cv::Mat *image, Results *results)
{
  _params = &params->GetDepthObstacleParams();
  _colorImage = image;
  _results = &results->GetDepthObstacleResults();
}

void DetectDepthObstacle::operator()()
{
  DetectHand();
  Process();
}

void DetectDepthObstacle::Process()
{
  cvtColor(*_colorImage, _grayImage, CV_BGR2GRAY);

  threshold(_grayImage, _maskImage, 0, 255, THRESH_BINARY);

  GaussianBlur(_grayImage, _grayImage, Size(-1, -1), 3);

  if (_params->GetMode() == DepthObstacleParams::Mode::HandHunting)
  {
    DetectHand();
    SeparateRegions();
  }
  else
    SeparateRegionsEqually();

  FindMaxInRegions();

  FindRowMax();
  FindColMax();

  SplitRowRegions();
  SplitColRegions();

  _rowRegion = Mat::zeros(HORZ_REGIONS, VERT_REGIONS, CV_8UC1);
}

void DetectDepthObstacle::PreProcess()
{
}

void DetectDepthObstacle::DetectHand()
{
  // TODO: detect position of hand

  // cv::Point handPosition(_grayImage.cols / 2, _grayImage.rows / 2);
  cv::Point handPosition(10, _grayImage.rows / 2);

  if (_params->GetMode() == DepthObstacleParams::Mode::HandHunting)
    _results->SetHandPosition(handPosition);
  else
    _results->SetHandPosition(Point(_grayImage.cols / 2, _grayImage.rows / 2));
}

void DetectDepthObstacle::SeparateRegions()
{
  int handOffsetX = 0;
  int handOffsetY = 0;
  if (_params->GetMode() == DepthObstacleParams::Mode::HandHunting)
  {
    handOffsetX = _grayImage.cols / 2 - _results->GetHandPosition().x;
    handOffsetY = _grayImage.rows / 2 - _results->GetHandPosition().y;
  }

  Point tl;
  Point br;

  int width = 0;
  int height = 0;
  int currentCol = 0;
  int currentRow = 0;

  for (int i = 0; i < VERT_REGIONS; ++i)
  {
    currentRow = 0;
    for (int j = 0; j < HORZ_REGIONS; ++j)
    {
      if (i == 0) tl.x = 0;
      if (i == VERT_REGIONS - 1) br.x = _grayImage.cols;
      if (j == 0) tl.y = 0;
      if (j == HORZ_REGIONS - 1) br.y = _grayImage.rows;

      tl.x = _results->GetHandPosition().x/_grayImage.cols + (i/(float)VERT_REGIONS - _params->GetCenterRegionsWidth()/2) * _grayImage.cols;

      width = ((i > 0 && i < VERT_REGIONS - 1) ? _grayImage.cols * _params->GetCenterRegionsWidth() : _grayImage.cols * (1 - 3 * _params->GetCenterRegionsWidth()) / 2.f);
      height = ((j > 0 && j < HORZ_REGIONS - 1) ? _grayImage.rows * _params->GetCenterRegionHeight() : _grayImage.rows * (1 - _params->GetCenterRegionHeight()) / 2.f);

      

      _results->SetRegionBounds(i, j, Rect(currentCol + handOffsetX, currentRow + handOffsetY, width, height) & Rect(0, 0, _grayImage.cols, _grayImage.rows));
      currentRow += height;
    }
    currentCol += width;
  }
}

void DetectDepthObstacle::SeparateRegionsEqually()
{

}

void DetectDepthObstacle::FindMaxInRegions()
{
  double minVal = 0;
  double maxVal = 0;

  for (int i = 0; i < HORZ_REGIONS; ++i)
  {
    for (int j = 0; j < VERT_REGIONS; ++j)
    {
      minMaxLoc(_grayImage(_results->GetRegionBounds(j, i)), &minVal, &maxVal);
      _results->SetRegionIntensity(j, i, minVal);

      // Histogram Calculation
      Mat hist;
      int size[] = { 256 };
      float range[] = { 0, 256 };
      const float* ranges[] = { range };
      int channels[] = { 0 };
      calcHist(&_grayImage(_regions[i * VERT_REGIONS + j]), 1, channels, _maskImage(_regions[i * VERT_REGIONS + j]), hist, 1, size, ranges, true, false);
      normalize(hist, hist, 0, hist.rows, NORM_MINMAX, -1, Mat());

      Mat histDisplay = Mat::zeros(257, 256, CV_8UC1);
      for (int k = 0; k < 256; ++k)
        histDisplay.at<char>(256 - hist.at<float>(k), k) = 255;
    }
  }
}

void DetectDepthObstacle::FindRowMax()
{
  _rowMax = Mat::zeros(1, _grayImage.rows, CV_8UC1);
  int pixel = 0;
  int rowMax = 0;

  for (int i = 0; i < _grayImage.rows; ++i)
  {
    rowMax = 255;

    for (int j = 0; j < _grayImage.cols; ++j)
    {
      pixel = _grayImage.at<char>(i, j);

      if (pixel > 0 && pixel < rowMax)
        rowMax = pixel;
    }

    _rowMax.at<char>(0, i) = rowMax;
  }
}

void DetectDepthObstacle::FindColMax()
{
  _colMax = Mat::zeros(1, _grayImage.cols, CV_8UC1);
  int pixel = 0;
  int columnMax = 0;

  for (int j = 0; j < _grayImage.cols; ++j)
  {
    columnMax = 255;

    for (int i = 0; i < _grayImage.rows; ++i)
    {
      pixel = _grayImage.at<char>(i, j);

      if (pixel > 0 && pixel < columnMax)
        columnMax = pixel;
    }

    _colMax.at<char>(0, j) = columnMax;
  }
}

void DetectDepthObstacle::SplitRowRegions()
{
  _rowRegion = Mat::zeros(1, HORZ_REGIONS, CV_8UC1);
  int numPixels = _rowMax.cols / HORZ_REGIONS;
  int pixel = 0;
  int regionMax = 0;

  for (int i = 0; i < HORZ_REGIONS; ++i)
  {
    regionMax = 255;
    
    for (int j = 0; j < numPixels; ++j)
    {
      pixel = _rowMax.at<char>(0, i*numPixels + j);

      if (pixel > 0 && pixel < regionMax)
        regionMax = pixel;
    }

    _rowRegion.at<char>(0, i) = regionMax;
  }
}

void DetectDepthObstacle::SplitColRegions()
{
  _colRegion = Mat::zeros(1, VERT_REGIONS, CV_8UC1);
  int numPixels = _colMax.cols / VERT_REGIONS;
  int pixel = 0;
  int regionMax = 0;

  for (int i = 0; i < VERT_REGIONS; ++i)
  {
    regionMax = 255;

    for (int j = 0; j < numPixels; ++j)
    {
      pixel = _colMax.at<char>(0, i*numPixels + j);

      if (pixel > 0 && pixel < regionMax)
        regionMax = pixel;
    }

    _colRegion.at<char>(0, i) = regionMax;
  }
}

void DetectDepthObstacle::Draw()
{
}

void DetectDepthObstacle::Display()
{
}

void DetectDepthObstacle::Clear()
{
}

// TODO: implement function to break region into 3x5, iterate over them, and send (x, y, width, height) to...
//       another function that finds the local maximum in that region.
// Rect region_of_interest = Rect(x, y, w, h);
