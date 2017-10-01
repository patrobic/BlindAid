#include "DepthObstacleDetection.h"

using namespace cv;

void DepthObstacleDetector::Init(const IDetectorParams *params, const cv::Mat *image, IDetectorResults *results)
{
  _params = static_cast<const DepthObstacleParams*>(params);
  _image = image;
  _results = static_cast<DepthObstacleResults*>(results);
}

void DepthObstacleDetector::Start()
{
  Process();
}

void DepthObstacleDetector::Process()
{
  cvtColor(*_image, _grayImage, CV_BGR2GRAY);

  threshold(_grayImage, _maskImage, 0, 255, THRESH_BINARY);

  GaussianBlur(_grayImage, _grayImage, Size(-1, -1), 3);

  SeparateRegions();
  FindMaxInRegions();

  FindRowMax();
  FindColMax();

  SplitRowRegions();
  SplitColRegions();

  _rowRegion = Mat::zeros(ROW_REGIONS, COL_REGIONS, CV_8UC1);
}

void DepthObstacleDetector::PreProcess()
{
}

void DepthObstacleDetector::SeparateRegions()
{
  int width = _grayImage.cols / COL_REGIONS;
  int height = _grayImage.rows / ROW_REGIONS;

  for (int i = 0; i < ROW_REGIONS; ++i)
  {
    for (int j = 0; j < COL_REGIONS; ++j)
    {
      _regions[i * COL_REGIONS + j].x = j * width;
      _regions[i * COL_REGIONS + j].y = i * height;
      _regions[i * COL_REGIONS + j].width = width;
      _regions[i * COL_REGIONS + j].height = height;
    }
  }
}

void DepthObstacleDetector::FindMaxInRegions()
{
  double minVal = 0;
  double maxVal = 0;
  for (int i = 0; i < ROW_REGIONS; ++i)
  {
    for (int j = 0; j < COL_REGIONS; ++j)
    {
      minMaxLoc(_grayImage(_regions[i * COL_REGIONS + j]), &minVal, &maxVal);
     
      _nearestDistance._regions[j][i] = minVal;
      _results->SetRegion(i, j, minVal);

      // Histogram Calculation
      Mat hist;
      int size[] = { 256 };
      float range[] = { 0, 256 };
      const float* ranges[] = { range };
      int channels[] = { 0 };
      calcHist(&_grayImage(_regions[i * COL_REGIONS + j]), 1, channels, _maskImage(_regions[i * COL_REGIONS + j]), hist, 1, size, ranges, true, false);
      normalize(hist, hist, 0, hist.rows, NORM_MINMAX, -1, Mat());

      Mat histDisplay = Mat::zeros(257, 256, CV_8UC1);
      for (int k = 0; k < 256; ++k)
        histDisplay.at<char>(256 - hist.at<float>(k), k) = 255;
    }
  }
}

void DepthObstacleDetector::FindRowMax()
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

void DepthObstacleDetector::FindColMax()
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

void DepthObstacleDetector::SplitRowRegions()
{
  _rowRegion = Mat::zeros(1, ROW_REGIONS, CV_8UC1);
  int numPixels = _rowMax.cols / ROW_REGIONS;
  int pixel = 0;
  int regionMax = 0;

  for (int i = 0; i < ROW_REGIONS; ++i)
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

void DepthObstacleDetector::SplitColRegions()
{
  _colRegion = Mat::zeros(1, COL_REGIONS, CV_8UC1);
  int numPixels = _colMax.cols / COL_REGIONS;
  int pixel = 0;
  int regionMax = 0;

  for (int i = 0; i < COL_REGIONS; ++i)
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

void DepthObstacleDetector::Draw()
{
}

void DepthObstacleDetector::Display()
{
}

void DepthObstacleDetector::Clear()
{
}

// TODO: implement function to break region into 3x5, iterate over them, and send (x, y, width, height) to...
//       another function that finds the local maximum in that region.
// Rect region_of_interest = Rect(x, y, w, h);