#include "ViewContainer.h"
#include "../BusinessLayer/BusinessContainer.h"
#include <SongPlayerUI/SongPlayerUi.h>
#include <ProgressBar/ProgressBar.h>
#include <SongPlayerView/SongPlayerView.h>

ViewContainer::ViewContainer(BusinessContainer& businessContainer)
    : SongPlayerUI_(new SongPlayerUi())
    , ProgressBar_(new ProgressBar())
    , SongPlayerView_(new SongPlayerView(businessContainer.songPlayer(),
                                         *SongPlayerUI_, *ProgressBar_))
{
}

ViewContainer::~ViewContainer()
{
}
