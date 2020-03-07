#include "BusinessContainer.h"
#include "CurrentSongPresenter.h"
#include "SongPlayerState.h"
#include "SongControlPresenter.h"
#include "SongController.h"
#include "SongState.h"
#include "SongPlayer.h"

#include "LocalSongUrlSource.h"

BusinessContainer::BusinessContainer()
    : songUrlSource_(new LocalSongUrlSource)
    , songState_(new SongState)
    , songPlayerState_(new SongPlayerState)
    , songPlayer_(new SongPlayer(*songState_))
    , songController_(new SongController(*songPlayer_, *songPlayerState_, *songUrlSource_))
    , currentSongPresenter_(new CurrentSongPresenter(*songState_))
    , songControlPresenter_(new SongControlPresenter(*songController_, *songPlayerState_))
{
}

BusinessContainer::~BusinessContainer()
{
}

I_CurrentSongPresenter &BusinessContainer::currentSongPresenter()
{
    return *currentSongPresenter_;
}

I_SongControlPresenter &BusinessContainer::songControlPresenter()
{
    return *songControlPresenter_;
}
