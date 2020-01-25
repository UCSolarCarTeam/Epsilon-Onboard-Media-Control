#pragma once
#include <QScopedPointer>
#include <QMediaPlayer>

#include "I_SongPlayer.h"

class I_SongEntity;
class I_SongController;

class SongPlayer : I_SongPlayer
{
public:
    SongPlayer(I_SongEntity& songEntity);

    // I_SongPlayer interface
public:
    void play() override;
    void pause() override;
    void load(const QMediaContent &content) override;

    // Slots
    void updateSongPosition();

private:
    QScopedPointer<QMediaPlayer> mediaPlayer_;
    I_SongEntity& songEntity_;
};

