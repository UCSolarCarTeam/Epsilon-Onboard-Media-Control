#ifndef WIRINGPIBUTTONS_HPP
#define WIRINGPIBUTTONS_HPP

#include <stdio.h> 
#include <wiringPi.h>
#include <chrono>

//using namespace std::chrono;

class WiringPiButtons
{
    public:
      enum Button { SPACE = 29, VOLUMEDOWN = 25, VOLUMEUP = 24, NEXT  = 23, PREVIOUS = 22, TOGGLEPLAY = 21, RELEASED = 0};
      WiringPiButtons();
      Button getEvents();  
      //run `gpio readall` on the pi to see the wiringPi numbering 

    private:
      void initButton(int buttonNumber);
      Button state;
      std::chrono::high_resolution_clock::time_point period_start;
      std::chrono::duration<double> deltaTime;
      Button returnButton;
};

#endif
