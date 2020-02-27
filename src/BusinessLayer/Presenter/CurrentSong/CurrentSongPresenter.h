#pragma once

#include "I_CurrentSongPresenter.h"

class CurrentSongPresenter : public I_CurrentSongPresenter
{
public:
    explicit CurrentSongPresenter(I_SongEntity& songEntity);
    ~CurrentSongPresenter() override;

public:
    I_SongEntity& songEntity() const override;

private:
    I_SongEntity& songEntity_;
};
