#include "SongPlayerUi.h"
#include "ProgressBar.h"
#include "CurrentSongView.h"
#include "SongControlView.h"
#include "ViewContainer.h"
#include "BusinessContainer.h"

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
