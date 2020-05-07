#include "CurrentSongPresenter.h"

CurrentSongPresenter::CurrentSongPresenter(I_SongState& songState)
    : songState_(songState)
{
}

CurrentSongPresenter::~CurrentSongPresenter()
{
}

I_SongState& CurrentSongPresenter::songState() const
{
    return songState_;
}
