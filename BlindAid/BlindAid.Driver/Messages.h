#pragma once

#include <string>

namespace Messages
{
  static std::string categories[][3] = {
    { "COMMAND", "FLAGS", "CATEGORY" },
    { "blindaid", "-a | -c | -t <path> | -s <path> -r [delay] [path]", "operation mode selection" },
    { "", "-d -v [level] -l", "debugging performance options" },
    { "", "-p <port> -cc <count>", "miscellaneous settings" },
    { "", "-do {fr | hp} -tl {dl | bd}", "processing module selection" },
    { "", "-coloroff | -depthoff", "image channel selection" },
    { "", "-?", "help" }
  };

  static std::string messages[][5] = {
    { "FLAG", "[ARGUMENT]", "DESCRIPTION", "DETAILS", "CHANGES" },
    { "a", "", "Realtime Mode", "bypass menu, no user interaction", "Camera ON /Glove ON" },
    { "c", "", "Camera Only", "disable glove, print control to screen", "Camera ON / Glove OFF" },
    { "t", "<path>", "Glove Only", "disable camera, load images from disk", "Camera OFF/Glove ON" },
    { "s", "<path>", "Simulate Mode", "disable performance optimizations", "Camera OFF/Glove OFF" },
    { "r", "[delay] [path]", "Record Enabled", "save images to disk, 0 for manual", "Record ON" },
    { "d", "", "Display Images", "show color/depth images to screen", "Display ON" },
    { "v", "[level]", "Verbose Messages", "print info messages to screen", "Logging ON" },
    { "l", "", "Low Performance", "disable multi threading optimizations", "Threads OFF" },
    { "p", "<port #>", "Set COM Port Number", "for Bluetooth glove connection", "" },
    { "cc", "[count]", "Set Consecutive Count", "number of detections before warning", "" },
    { "do", "{fr | hp}", "Depth Obstacle Mode", "fixed regions/hand position", "DepthObstacle FR/HP" },
    { "tl", "{dl | bd}", "Traffic Light Mode", "deep learning/blob detector", "TrafficLight DL/BD" },
    { "coloroff", "", "Depth Image Only", "disable color stream processing", "Color OFF" },
    { "depthoff", "", "Color Image Only", "disable depth stream processing", "Depth OFF" },
    { "smooth", "[count]", "Depth Frame Smoothing ", "take consecutive max to reduce noise", "" },
    { "conf", "[confidence]", "Minimum Red Confidence", "confidence required to detect red", "" },
    { "colordim", "<w> [h]", "Color Image Dimensions", "color image width and height ratios", "" },
    { "depthdim", "<w> [h]", "Depth Image Dimensions", "depth image width and height ratios", "" },
    { "ignore", "[ignore]", "Percentile to Ignore", "near end of histogram ratio to ignore", "" },
    { "valid", "[valid]", "Valid Ratio Threshold", "minimum ratio of non-zero depth pixels", "" },
    { "?", "", "Show Help", "show flag descriptions", "" },
    { "m", "", "Manual Launch", "user entry of arguments", "" },
    { "q", "", "Quit Program", "exit main program menu", "" },
    { "o", "", "Depth Obstacle", "test depth by loading from disk", "" },
    { "l", "", "Traffic Light", "test color by loading from disk", "" }
  };

  static std::string scenarios[][4] = {
    { "COMMAND ", "FLAGS", "DESCRIPTION", "PURPOSE" },
    { "blindaid", "", "Menu Interface", "manual configuration, via interactive menu" },
    { "blindaid", "-a", "Realtime Final", "complete experience, for final product demo" },
    { "blindaid", "-c", "Capture Only", "to demo without glove, print control to screen" },
    { "blindaid", "-t path", "Control Only", "to demo without camera, load images from disk" },
    { "blindaid", "-s path", "Simulate All", "disable camera and glove, only test software loop" },
    { "blindaid", "-r ms", "Record Images", "save images periodically, or 0 for manual trigger" },
    { "blindaid", "-a -d", "Realtime w\\Debug", "full experience w\\image display, low performance" },
    { "blindaid", "-c -d", "Capture w\\Debug", "capture only w\\display, to demonstrate processing" },
  };
}