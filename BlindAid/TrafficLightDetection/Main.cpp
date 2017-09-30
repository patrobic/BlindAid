#include<iostream>

using namespace std;

#include "TrafficLightDetector.h"

#define PATH "C:\\Projects\\BlindAid\\TestImages\\"

void main()
{
  string names[] = { "tlight2.jpg", "tlight3.jpg", "tlight4.jpg", "tlight5.jpg" };

  TrafficLightDetector tld;

  for(int i = 0; i < 4 ; ++i)
    tld.DetectTrafficLight(PATH + names[i]);
}