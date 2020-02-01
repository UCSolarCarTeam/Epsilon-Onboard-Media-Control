#pragma once

class I_SongController
{
public:
    virtual ~I_SongController(){}

    virtual void play() = 0;
    virtual void pause() = 0;
    virtual void playNext() = 0;
    virtual void playPrevious() = 0;
};
