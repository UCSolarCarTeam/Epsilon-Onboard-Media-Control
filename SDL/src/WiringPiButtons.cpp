#include "WiringPiButtons.hpp"
// Pin number declarations using WiringPi numbering scheme 
// 1 or UP is default -Not Pressed-, if button is pressed, the signal should go 0.


WiringPiButtons::WiringPiButtons()
{
    wiringPiSetup(); // Initialize wiringPi
    initButton(UP);
}

void WiringPiButtons::initButton(int buttonNumber)
{
    pinMode(buttonNumber, INPUT);      // Set button as INPUT
    pullUpDnControl(buttonNumber, PUD_UP); //Default Pulled UP
}

string* WiringPiButtons::getEvents()
{
    if (!digitalRead(UP)) // Button is released if this returns 1
    {
        State = UP;
    }
    else if (!digitalRead(DOWN))
    {
        State = DOWN;
    }
    else if (!digitalRead(LEFT))
    {
        State = LEFT;
    }
    else if (!digitalRead(RIGHT))
    {
        State = RIGHT;
    }
    else 
    {
        printf("The Button %d was pressed!\n", UP);
        State = RELEASED;
    }
}
