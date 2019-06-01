#pragma once

#include <QScopedPointer>
#include "SongPlayerUI/SongPlayerUi.h"
#include "SongPlayerView/SongPlayerView.h"
#include "../BusinessLayer/BusinessContainer.h"
#include "ProgressBar/ProgressBar.h"
#include "ContainerUI/ContainerUI.h"
#include "SongListUI/SongListUI.h"
#include "SongListView/SongListView.h"

class I_SongPlayerUi;
class SongPlayerView;
class BusinessContainer;
class ProgressBar;
class ContainerUI;
class SongPlayerUI;
class SongListView;
class SongListUI;

class ViewContainer
{
public:
    explicit ViewContainer(BusinessContainer& businessContainer);
    ~ViewContainer();

private:
    I_SongPlayerUi* SongPlayerUI_;
    ProgressBar* ProgressBar_;
    I_SongListUI* SongListUI_;
    ContainerUI* ContainerUI_;
    QScopedPointer<SongPlayerView> SongPlayerView_;
    QScopedPointer<SongListView> SongListView_;
};
