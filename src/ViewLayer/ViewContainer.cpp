#include "BusinessContainer.h"
#include "CurrentSongView.h"
#include "ProgressBar.h"
#include "SongControlView.h"
#include "SongPlayerUi.h"
#include "ViewContainer.h"

ViewContainer::ViewContainer(BusinessContainer& businessContainer)
    : songPlayerUI_(new SongPlayerUi())
    , progressBar_(new ProgressBar())
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
