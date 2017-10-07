#include "DetectDepthObstacle.h"

using namespace std;
using namespace cv;

void DetectDepthObstacle::operator()()
{
  DetectHand();
  Process();
}

void DetectDepthObstacle::Process()
{
  cvtColor(*_input->GetDepthImage(), _grayImage, CV_BGR2GRAY);

  threshold(_grayImage, _maskImage, 0, 255, THRESH_BINARY);

  GaussianBlur(_grayImage, _grayImage, Size(-1, -1), 3);

  if (_params->GetMode() == Parameters::Mode::HandHunting)
  {
    DetectHand();
    SeparateRegions();
  }
  else
  {
    _output->SetHandPosition(Point(_grayImage.cols / 2, _grayImage.rows / 2));
    SeparateRegionsEqually();
  }

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

  _output->SetHandPosition(Point(_grayImage.cols / 2, _grayImage.rows / 2));
}

void DetectDepthObstacle::SeparateRegions()
{
  Point tl;
  Point br;

  for (int i = 0; i < VERT_REGIONS; ++i)
  {
    for (int j = 0; j < HORZ_REGIONS; ++j)
    {
      tl.x = _output->GetHandPosition().x + (int)((i - 2.5) * _grayImage.cols * _params->GetCenterRegionsWidth());
      br.x = _output->GetHandPosition().x + (int)((i - 1.5) * _grayImage.cols * _params->GetCenterRegionsWidth());
      tl.y = _output->GetHandPosition().y + (int)((j - 1.5) * _grayImage.rows * _params->GetCenterRegionHeight());
      br.y = _output->GetHandPosition().y + (int)((j - 0.5) * _grayImage.rows * _params->GetCenterRegionHeight());

      if (i == 0) tl.x = 0;
      if (i == VERT_REGIONS - 1) br.x = _grayImage.cols;
      if (j == 0) tl.y = 0;
      if (j == HORZ_REGIONS - 1) br.y = _grayImage.rows;

      _output->SetRegionBounds(i, j, Rect(tl, br) & Rect(0, 0, _grayImage.cols, _grayImage.rows));
    }
  }
}

void DetectDepthObstacle::SeparateRegionsEqually()
{
  int width = _grayImage.cols / VERT_REGIONS;
  int height = _grayImage.rows / HORZ_REGIONS;

  for (int i = 0; i < HORZ_REGIONS; ++i)
  {
    for (int j = 0; j < VERT_REGIONS; ++j)
    {
      _regions[i * VERT_REGIONS + j].x = j * width;
      _regions[i * VERT_REGIONS + j].y = i * height;
      _regions[i * VERT_REGIONS + j].width = width;
      _regions[i * VERT_REGIONS + j].height = height;

      _output->SetRegionBounds(j, i, _regions[i * VERT_REGIONS + j] & Rect(0, 0, _grayImage.cols, _grayImage.rows));
    }
  }
}

void DetectDepthObstacle::FindMaxInRegions()
{
  double minVal = 0;
  double maxVal = 0;

  for (int i = 0; i < HORZ_REGIONS; ++i)
  {
    for (int j = 0; j < VERT_REGIONS; ++j)
    {
      minMaxLoc(_grayImage(_output->GetRegionBounds(j, i)), &minVal, &maxVal);
      _output->SetRegionIntensity(j, i, minVal);

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
