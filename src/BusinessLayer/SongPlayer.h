#pragma once
#include <QScopedPointer>
#include <QMediaPlayer>

#include "I_SongPlayer.h"

class I_SongEntity;

class SongPlayer : public I_SongPlayer
{
public:
    explicit SongPlayer(I_SongEntity& songEntity);
    ~SongPlayer() override;

    void play() override;
    void pause() override;
    void load(const QMediaContent& content) override;
    void changeVolume(int volume) override;

public slots:
    void updateSongPosition(qint64 pos) override;
    void songUpdate(const QMediaContent&) override;

private:
    QScopedPointer<QMediaPlayer> mediaPlayer_;
    I_SongEntity& songEntity_;

};

