#include "WiringPiButtons.hpp"
// Pin number declarations using WiringPi numbering scheme 
// 1 or UP is default -Not Pressed-, if button is pressed, the signal should go 0.
// Will only accept calls 10 times a second, this is a simple way to debounce


WiringPiButtons::WiringPiButtons()
{
    wiringPiSetup(); // Initialize wiringPi
    initButton(UP);
    initButton(DOWN);
    initButton(LEFT);
    initButton(RIGHT);
    State = RELEASED;
    period_start = high_resolution_clock::now()
}

void WiringPiButtons::initButton(int buttonNumber)
{
    pinMode(buttonNumber, INPUT);      // Set button as INPUT
    pullUpDnControl(buttonNumber, PUD_UP); //Default Pulled UP
}

string* WiringPiButtons::getEvents()
{

    deltaTime = duration_cast<duration<double>>(high_resolution_clock::now() - period_start);
    if (deltaTime.count() < 0.10)
    {
        printf("delta is %lf \n", deltaTime.count());
        return;
    }
    period_start = high_resolution_clock::now(); 

    switch(State)
    {
        case RELEASED:
            if (!digitalRead(UP))       { State = UP; }
            if (!digitalRead(DOWN))     { State = DOWN; }
            if (!digitalRead(LEFT))     { State = LEFT; }
            if (!digitalRead(RIGHT))    { State = RIGHT; }
            break;
        case UP:
            if (digitalRead(UP))
            {
                printf("From UP Button %d was pressed!\n", State);
                State = RELEASED; 
            }
            break;
        case DOWN:
            if (digitalRead(DOWN)) 
            {
                printf("From DOWN Button %d was pressed!\n", State);
                State = RELEASED; 
            }
            break;
        case LEFT:
            if (digitalRead(LEFT))
            {
                printf("From LEFT Button %d was pressed!\n", State);
                State = RELEASED; 
            }
            break;
        case RIGHT:
            if (digitalRead(RIGHT)) 
            {
                printf("From RIGHT Button %d was pressed!\n", State);
                State = RELEASED; 
            }
            break;
    }
}
