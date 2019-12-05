#pragma once

class I_SongPlayerPresenter
{
public:
    virtual ~I_SongPlayerPresenter();
    virtual void play() = 0;
    virtual void pause() = 0;
    virtual void prev() = 0;
    virtual void next() = 0;
    virtual void loop() = 0;
    virtual void shuffle() = 0;
};
