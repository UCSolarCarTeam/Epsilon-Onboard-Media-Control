#include "WiringPiButtons.hpp"
// Pin number declarations using WiringPi numbering scheme 


WiringPiButtons::WiringPiButtons()
{
    wiringPiSetup(); // Initialize wiringPi
    initButton(UP);
}

void WiringPiButtons::initButton(int buttonNumber)
{
    pinMode(buttonNumber, INPUT);      // Set button as INPUT
    pullUpDnControl(buttonNumber, PUD_DOWN); //Set DOWN
}

string* WiringPiButtons::getEvents()
{
    if (digitalRead(UP)) // Button is released if this returns 1
    {
        delay(100);
        printf("NOT PRESSED!!\n");
    }
    else
    {
        delay(100);
        printf("Button Pressed!\n");
    }
}
