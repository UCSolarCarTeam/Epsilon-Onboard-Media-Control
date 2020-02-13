#include "BusinessContainer.h"
#include "CurrentSongPresenter.h"
#include "SongControlEntity.h"
#include "SongControlPresenter.h"
#include "SongController.h"
#include "SongEntity.h"
#include "SongPlayer.h"

#include "LocalSongUrlSource.h"

BusinessContainer::BusinessContainer()
    : songUrlSource_(new LocalSongUrlSource)
    , songEntity_(new SongEntity)
    , songControlEntity_(new SongControlEntity)
    , songPlayer_(new SongPlayer(*songEntity_))
    , songController_(new SongController(*songPlayer_, *songControlEntity_, *songUrlSource_))
    , currentSongPresenter_(new CurrentSongPresenter(*songEntity_))
    , songControlPresenter_(new SongControlPresenter(*songController_, *songControlEntity_))
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
