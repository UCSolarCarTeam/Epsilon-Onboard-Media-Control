#include "WiringPiButtons.hpp"
// Pin number declarations using WiringPi numbering scheme 

const int butPin25 = 25;


int main(void)
{
    wiringPiSetup(); // Initialize wiringPi

    pinMode(butPin, INPUT);      // Set button as INPUT

    // Loop (while(1)):
    while(1)
    {
        if (digitalRead(butPin)) // Button is released if this returns 1
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

    return 0;
}

