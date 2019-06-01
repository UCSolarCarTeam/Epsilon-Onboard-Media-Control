#include "ViewContainer.h"

ViewContainer::ViewContainer(BusinessContainer& businessContainer)
    : SongPlayerUI_(new SongPlayerUi())
    , ProgressBar_(new ProgressBar())
    , SongListUI_(new SongListUI())
    , ContainerUI_(new ContainerUI())
    , SongPlayerView_(new SongPlayerView(businessContainer.songPlayer(),
                                         *SongPlayerUI_, *ProgressBar_,
                                         *ContainerUI_))
    , SongListView_(new SongListView(businessContainer.songPlayer(),*SongListUI_, *ContainerUI_))
{
    ContainerUI_->addWidget(SongPlayerUI_);
    ContainerUI_->setCurrentIndex(0);
    ContainerUI_->addWidget(SongListUI_);
}

ViewContainer::~ViewContainer()
{
}
