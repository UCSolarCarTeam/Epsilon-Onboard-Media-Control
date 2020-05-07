#pragma once

class I_SongState;

class I_CurrentSongPresenter
{
public:
    virtual ~I_CurrentSongPresenter() {}

    virtual I_SongState& songState() const = 0;
};
