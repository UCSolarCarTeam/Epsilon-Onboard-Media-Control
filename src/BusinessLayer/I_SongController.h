#pragma once

class I_SongController
{
public:
    virtual ~I_SongController(){}

    virtual void togglePlay() = 0;
    virtual void pause() = 0;
    virtual void playNext() = 0;
    virtual void playPrevious() = 0;
    virtual void toggleLoop() = 0;
    virtual void toggleShuffle() = 0;
};
