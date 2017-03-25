#pragma once
#include <QObject>

class SongPlayer;
class I_SongPlayerUi;

class SongPlayerView : public QObject
{
public:
    SongPlayerView(SongPlayer& songPlayer, I_SongPlayerUi ui);
    void handlePlayPauseClicked();

private:
    SongPlayerUi& ui_;
    SongPlayer& songPlayer_;
};
