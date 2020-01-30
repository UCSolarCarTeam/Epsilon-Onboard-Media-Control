#pragma once

class ISongcontroller
{
public:
    virtual ~ISongcontroller(){}

    virtual void playNext() = 0;
    virtual void playPrevious() = 0;
};
