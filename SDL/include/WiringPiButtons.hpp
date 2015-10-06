#ifndef WIRINGPIBUTTONS_HPP
#define WIRINGPIBUTTONS_HPP


#include <stdio.h> 
#include <wiringPi.h>



class WiringPiButtons()
{
    public:
      string* getEvents();  

    private:
      enum Button { UP = 25, DOWN = 24, LEFT  = 23, RIGHT = 22 };

};

#endif
