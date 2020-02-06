#include "SongControlPresenter.h"
#include "I_SongControlEntity.h"
#include "I_SongController.h"

SongControlPresenter::SongControlPresenter(I_SongController &songController,
                                           I_SongControlEntity &songEntity)
                                           : songController_(songController),
                                             songEntity_(songEntity)
{}

void SongControlPresenter::togglePlay()
{
    songController_.togglePlay();
}

void SongControlPresenter::playNext()
{
    songController_.playNext();
}

void SongControlPresenter::playPrevious()
{
    songController_.playPrevious();
}

void SongControlPresenter::toggleShuffle()
{
    songController_.toggleShuffle();
}

void SongControlPresenter::toggleLoop()
{
    songController_.toggleLoop();
}

I_SongControlEntity &SongControlPresenter::songControlEntity() const
{
    return songEntity_;
}
