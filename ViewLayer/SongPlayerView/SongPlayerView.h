#pragma once
#include <QObject>
#include "SongPlayerUI/I_SongPlayerUi.h"

class SongPlayer;
class I_SongPlayerUi;

class SongPlayerView : public QWidget
{
public:
    SongPlayerView(SongPlayer& songPlayer, I_SongPlayerUi& ui);
    ~SongPlayerView();
    void handlePlayPauseClicked();
    void handlePlayButtonClicked();
    void handleOpenButtonClicked();

private:
    I_SongPlayerUi& ui_;
    SongPlayer& songPlayer_;
};
