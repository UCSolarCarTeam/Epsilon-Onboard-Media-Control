#include "SongControlPresenter.h"
#include "I_SongPlayerState.h"
#include "I_SongController.h"

SongControlPresenter::SongControlPresenter(I_SongController& songController,
        I_SongPlayerState& songState)
    : songController_(songController),
      songState_(songState)
{
}

SongControlPresenter::~SongControlPresenter()
{
}

void SongControlPresenter::playNext()
{
    songController_.playNext();
}

void SongControlPresenter::playPrevious()
{
    songController_.playPrevious();
}

I_SongPlayerState& SongControlPresenter::songPlayerState() const
{
    return songState_;
}
