#include "SongPlayerUI/SongPlayerUi.h"
#include "ProgressBar/ProgressBar.h"
#include "CurrentSongView.h"
#include "SongControlView.h"
#include "ViewContainer.h"
#include "../BusinessLayer/BusinessContainer.h"

ViewContainer::ViewContainer(BusinessContainer& businessContainer)
    : songPlayerUI_(new SongPlayerUi())
    , progressBar_(new ProgressBar())
//    , SongPlayerView_(new SongPlayerView(businessContainer.songPlayer(),
//                                         *SongPlayerUI_, *ProgressBar_))
    , currentSongView_(new CurrentSongView(businessContainer.currentSongPresenter(),
                                           *songPlayerUI_,
                                           *progressBar_))
    , songControlView_(new SongControlView(businessContainer.songControlPresenter(),
                                           *songPlayerUI_))
{
}

ViewContainer::~ViewContainer()
{
}
