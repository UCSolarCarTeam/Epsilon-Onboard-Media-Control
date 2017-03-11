#include "SongPlayerUI/SongPlayerUi.h"
#include "SongPlayerView/SongPlayerView.h"
#include "../BusinessLayer/BusinessContainer.h"
#include "ViewContainer.h"

ViewContainer::ViewContainer(BusinessContainer& BusinessContainer)
    : SongPlayerUI_(new SongPlayerUI())
    , SongPlayerView_(new SongPlayerView(
                          *SongPlayerUI_))
{
}

ViewContainer::~ViewContainer()
{
}
