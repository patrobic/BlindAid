#include<iostream>

using namespace std;

#include "TrafficLightDetector.h"
#include "Parameters.h"

#define PATH "C:\\Projects\\BlindAid\\TestImages\\"
string names[] = { "tlight2.jpg", "tlight3.jpg", "tlight4.jpg", "tlight5.jpg" };

void main()
{
  Parameters params;
  params._streetLightParams._mode = StreetLightParams::FindContoursMode;

  TrafficLightDetector tld(params._streetLightParams);

  for(int i = 0; i < 4 ; ++i)
    tld.DetectTrafficLight(PATH + names[i]);
}