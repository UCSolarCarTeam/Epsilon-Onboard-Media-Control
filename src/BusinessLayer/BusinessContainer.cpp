#include "BusinessContainer.h"
#include "CurrentSongPresenter.h"
#include "ExternalContainer.h"
#include "SongController.h"
#include "SongControlPresenter.h"
#include "SongPlayer.h"
#include "SongPlayerState.h"
#include "SongState.h"

BusinessContainer::BusinessContainer(ExternalContainer& external)
    : songState_(new SongState)
    , songPlayerState_(new SongPlayerState)
    , songPlayer_(new SongPlayer(*songState_))
    , songController_(new SongController(*songPlayer_, *songPlayerState_, external.localSongUrlSource()))
    , currentSongPresenter_(new CurrentSongPresenter(*songState_))
    , songControlPresenter_(new SongControlPresenter(*songController_, *songPlayerState_))
{
}

BusinessContainer::~BusinessContainer()
{
}

I_CurrentSongPresenter& BusinessContainer::currentSongPresenter()
{
    return *currentSongPresenter_;
}

I_SongControlPresenter& BusinessContainer::songControlPresenter()
{
    return *songControlPresenter_;
}
