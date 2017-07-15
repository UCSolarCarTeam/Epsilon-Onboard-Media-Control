#include "ViewContainer.h"

ViewContainer::ViewContainer(BusinessContainer& businessContainer)
    : SongPlayerUI_(new SongPlayerUi())
    , SongPlayerView_(new SongPlayerView(businessContainer.songPlayer(),
                                         *SongPlayerUI_))
{
}

ViewContainer::~ViewContainer()
{
}
