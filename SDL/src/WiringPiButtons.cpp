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
    state = RELEASED;
    period_start = std::chrono::high_resolution_clock::now();
    returnButton = RELEASED;
}

void WiringPiButtons::initButton(int buttonNumber)
{
    pinMode(buttonNumber, INPUT);      // Set button as INPUT
    pullUpDnControl(buttonNumber, PUD_UP); //Default Pulled UP
}

Button WiringPiButtons::getEvents()
{

    deltaTime = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - period_start);
    if (deltaTime.count() < 0.04)
    {
        return 0;
    }
    period_start = std::chrono::high_resolution_clock::now(); 

    switch(state)
    {
        case RELEASED:
            if (returnButton != 0)
            {
                int tempValue = returnButton;
                returnButton = 0;
	        printf("FUNCTION returned %d\n",tempValue);
                return tempValue; 
            }

            if (!digitalRead(UP))      
                state = UP; 

            if (!digitalRead(DOWN))    
                state = DOWN; 

            if (!digitalRead(LEFT))
                state = LEFT;

            if (!digitalRead(RIGHT))  
                state = RIGHT; 

            break;
        case UP:
            if (digitalRead(UP))
            {
                printf("From UP Button %d was pressed!\n", state);
                returnButton = UP;
                state = RELEASED; 
            }
            break;
        case DOWN:
            if (digitalRead(DOWN)) 
            {
                printf("From DOWN Button %d was pressed!\n", state);
                returnButton = DOWN;
                state = RELEASED; 
            }
            break;
        case LEFT:
            if (digitalRead(LEFT))
            {
                printf("From LEFT Button %d was pressed!\n", state);
                returnButton = LEFT;
                state = RELEASED; 
            }
            break;
        case RIGHT:
            if (digitalRead(RIGHT)) 
            {
                printf("From RIGHT Button %d was pressed!\n", state);
                returnButton = RIGHT;
                state = RELEASED; 
            }
            break;
    }
}
