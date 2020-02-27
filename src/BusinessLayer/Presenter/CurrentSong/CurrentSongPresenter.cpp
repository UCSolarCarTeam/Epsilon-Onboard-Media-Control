#include "CurrentSongPresenter.h"

CurrentSongPresenter::CurrentSongPresenter(I_SongEntity& songEntity)
    : songEntity_(songEntity)
{
}

CurrentSongPresenter::~CurrentSongPresenter()
{
}

I_SongEntity& CurrentSongPresenter::songEntity() const
{
    return songEntity_;
}
