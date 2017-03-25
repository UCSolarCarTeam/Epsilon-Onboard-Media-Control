#pragma once
#include <QObject>

class SongPlayer;
class I_SongPlayerUi;

class SongPlayerView : public I_SongPlayerUi
{
public:
    SongPlayerView(SongPlayer& songPlayer, I_SongPlayerUi ui);
    void handlePlayPauseClicked();

private:
    I_SongPlayerUi& ui_;
    SongPlayer& songPlayer_;
};
