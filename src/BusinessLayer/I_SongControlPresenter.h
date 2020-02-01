#pragma once

class I_SongControlEntity;

class I_SongControlPresenter
{
public:
    virtual ~I_SongControlPresenter(){}

    virtual void togglePlay() = 0;
    virtual void playNext() = 0;
    virtual void playPrevious() = 0;
    virtual void toggleShuffle() = 0;
    virtual void toggleLoop() = 0;

    virtual I_SongControlEntity& songControlEntity() const = 0;
};
