#pragma once

class I_SongPlayerState;

class I_SongControlPresenter
{
public:
    virtual ~I_SongControlPresenter() {}

    virtual void playNext() = 0;
    virtual void playPrevious() = 0;
    virtual I_SongPlayerState& songPlayerState() const = 0;
};
