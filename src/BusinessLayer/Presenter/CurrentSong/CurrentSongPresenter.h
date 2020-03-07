#pragma once

#include "I_CurrentSongPresenter.h"

class CurrentSongPresenter : public I_CurrentSongPresenter
{
public:
    explicit CurrentSongPresenter(I_SongState& songState);
    virtual ~CurrentSongPresenter();

    I_SongState& songState() const override;

private:
    I_SongState& songState_;
};
