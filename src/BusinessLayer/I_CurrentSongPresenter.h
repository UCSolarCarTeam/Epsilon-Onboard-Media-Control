#pragma once

class I_SongEntity;

class I_CurrentSongPresenter
{
public:
    virtual ~I_CurrentSongPresenter(){}

    virtual I_SongEntity& songEntity() const = 0;
};
