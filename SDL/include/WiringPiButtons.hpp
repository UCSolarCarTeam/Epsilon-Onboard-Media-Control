#ifndef WIRINGPIBUTTONS_HPP
#define WIRINGPIBUTTONS_HPP


#include <stdio.h> 
#include <wiringPi.h>
#include <chrono>

class WiringPiButtons
{
    public:
      WiringPiButtons();
      string* getEvents();  

    private:
      enum Button { UP = 25, DOWN = 24, LEFT  = 23, RIGHT = 22, RELEASED = 0};
      void initButton(int buttonNumber);
      Button State;
      high_resolution_clock::time_point period_start;
      duration<double> deltaTime;
};

#endif
