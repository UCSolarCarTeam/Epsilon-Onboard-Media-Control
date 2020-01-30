#pragma once
#include <QScopedPointer>
#include <QMediaPlayer>

#include "I_SongPlayer.h"

class I_SongEntity;
class I_SongController;

class SongPlayer : public I_SongPlayer
{
public:
    SongPlayer(I_SongEntity& songEntity);

    // I_SongPlayer interface
    void play() override;
    void pause() override;
    void load(const QMediaContent &content) override;

public slots:
    void updateSongPosition(qint64 pos) override;
    void songUpdate(const QMediaContent&) override;

private:
    QScopedPointer<QMediaPlayer> mediaPlayer_;
    I_SongEntity& songEntity_;
};

