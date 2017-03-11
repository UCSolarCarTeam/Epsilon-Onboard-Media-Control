#pragma once
#include <QObject>

class SongPlayer;
class SongPlayerUi;

class SongPlayerView : public QObject
{
public:
    SongPlayerView(SongPlayer& songPlayer, SongPlayerUi& ui);
    void handlePlayButtonClicked();

private:

    SongPlayerUi& ui_;
    SongPlayer& songPlayer_;
};
