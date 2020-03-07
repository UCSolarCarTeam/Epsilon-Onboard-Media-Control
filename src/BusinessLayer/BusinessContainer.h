#pragma once

#include <QScopedPointer>
class ExternalContainer;
class I_SongController;
class SongPlayer;
class I_SongState;
class I_SongPlayerState;
class I_SongUrlSource;
class I_CurrentSongPresenter;
class I_SongControlPresenter;

class BusinessContainer
{
public:
    explicit BusinessContainer(ExternalContainer& external);
    ~BusinessContainer();

    I_CurrentSongPresenter& currentSongPresenter();
    I_SongControlPresenter& songControlPresenter();

private:
    QScopedPointer<I_SongState> songState_;
    QScopedPointer<I_SongPlayerState> songPlayerState_;
    QScopedPointer<SongPlayer> songPlayer_;
    QScopedPointer<I_SongController> songController_;

    QScopedPointer<I_CurrentSongPresenter> currentSongPresenter_;
    QScopedPointer<I_SongControlPresenter> songControlPresenter_;
};
