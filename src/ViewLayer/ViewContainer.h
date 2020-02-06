#pragma once

#include <QScopedPointer>

class I_SongPlayerUi;
class SongPlayerView;
class BusinessContainer;
class ProgressBar;
class ContainerUI;
class SongPlayerUI;
class SongListView;
class I_SongListUI;

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
