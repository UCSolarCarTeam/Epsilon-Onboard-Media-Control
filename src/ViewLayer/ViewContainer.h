#pragma once

#include <QScopedPointer>

class SongPlayerUi;
class SongPlayerView;
class BusinessContainer;
class ProgressBar;
class CurrentSongView;
class SongControlView;

class ViewContainer
{
public:
    explicit ViewContainer(BusinessContainer& businessContainer);
    ~ViewContainer();

private:
    QScopedPointer<SongPlayerUi> songPlayerUI_;
    ProgressBar* progressBar_;
//    QScopedPointer<SongPlayerView> SongPlayerView_;

    QScopedPointer<CurrentSongView> currentSongView_;
    QScopedPointer<SongControlView> songControlView_;
};
