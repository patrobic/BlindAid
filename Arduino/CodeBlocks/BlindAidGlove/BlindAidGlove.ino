#include <Arduino.h>
#include "Functions.h"

void setup()
{
	bool connected = false;
	Serial.begin(9600);

    InitializePins();

//    while(!connected)
//    {
//        Serial.begin(9600);
//        Serial.print("Connection failed!");
//    }

    Serial.print("Connected!");
}

void loop()
{
    ReceiveData();
    ParseValues();
    ControlMotors();
    //SendResponse();
}
