#include "WiringPiButtons.hpp"
// Pin number declarations using WiringPi numbering scheme 
// 1 or UP is default -Not Pressed-, if button is pressed, the signal should go 0.
// Will only accept calls 10 times a second, this is a simple way to debounce


WiringPiButtons::WiringPiButtons()
{
    wiringPiSetup(); // Initialize wiringPi
    initButton(SPACE);
    initButton(VOLUMEDOWN);
    initButton(VOLUMEUP);
    initButton(NEXT);
    initButton(PREVIOUS);
    initButton(TOGGLEPLAY);
    state = RELEASED;
    period_start = std::chrono::high_resolution_clock::now();
    returnButton = RELEASED;
}

void WiringPiButtons::initButton(int buttonNumber)
{
    pinMode(buttonNumber, INPUT);      // Set button as INPUT
    pullUpDnControl(buttonNumber, PUD_UP); //Default Pulled UP
}

WiringPiButtons::Button WiringPiButtons::getEvents()
{

    deltaTime = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - period_start);
    if (deltaTime.count() < 0.04)
    {
        return RELEASED;
    }
    period_start = std::chrono::high_resolution_clock::now(); 

    switch(state)
    {
        case RELEASED:
            if (returnButton != 0)
            {
                Button tempValue = returnButton;
                returnButton = RELEASED;
	            printf("FUNCTION returned %d\n",tempValue);
                return tempValue; 
            }

            if (!digitalRead(VOLUMEDOWN))      
                state = VOLUMEDOWN; 

            if (!digitalRead(VOLUMEUP))    
                state = VOLUMEUP; 

            if (!digitalRead(NEXT))
                state = NEXT;

            if (!digitalRead(PREVIOUS))  
                state = PREVIOUS; 
            
            if (!digitalRead(TOGGLEPLAY))  
                state = TOGGLEPLAY; 
            break;
        case VOLUMEDOWN:
            if (digitalRead(VOLUMEDOWN))
            {
                returnButton = VOLUMEDOWN;
                state = RELEASED; 
            }
            break;
        case VOLUMEUP:
            if (digitalRead(VOLUMEUP)) 
            {
                returnButton = VOLUMEUP;
                state = RELEASED; 
            }
            break;
        case NEXT:
            if (digitalRead(NEXT))
            {
                returnButton = NEXT;
                state = RELEASED; 
            }
            break;
        case PREVIOUS:
            if (digitalRead(PREVIOUS)) 
            {
                returnButton = PREVIOUS;
                state = RELEASED; 
            }
            break;
        case TOGGLEPLAY:
            if (digitalRead(TOGGLEPLAY)) 
            {
                returnButton = TOGGLEPLAY;
                state = RELEASED; 
            }
            break;
    }
}
