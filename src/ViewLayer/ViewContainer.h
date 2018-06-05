#pragma once

#include <QScopedPointer>
#include "SongPlayerUI/SongPlayerUi.h"
#include "SongPlayerView/SongPlayerView.h"
#include "../BusinessLayer/BusinessContainer.h"
#include "ProgressBar/ProgressBar.h"

class I_SongPlayerUi;
class SongPlayerView;
class BusinessContainer;
class ProgressBar;

class ViewContainer
{
public:
    explicit ViewContainer(BusinessContainer& businessContainer);
    ~ViewContainer();

private:
    I_SongPlayerUi* SongPlayerUI_;
    ProgressBar* ProgressBar_;
    QScopedPointer<SongPlayerView> SongPlayerView_;
};
