#pragma once

#include <QMediaPlayer>
#include <QScopedPointer>

#include "I_SongPlayer.h"

class I_SongState;

class SongPlayer : public I_SongPlayer
{
    Q_OBJECT
public:
    explicit SongPlayer(I_SongState& songState);
    virtual ~SongPlayer();

    void play() override;
    void pause() override;
    void load(const QMediaContent& content) override;
    void changeVolume(const int volume) override;

private slots:
    void updateSongPosition(qint64 pos);
    void updateSongDuration(qint64 pos);
    void updateSong();

private:
    QScopedPointer<QMediaPlayer> mediaPlayer_;
    I_SongState& songState_;

};

