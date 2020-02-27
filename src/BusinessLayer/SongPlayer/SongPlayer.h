#pragma once
#include <QScopedPointer>
#include <QMediaPlayer>

#include "I_SongPlayer.h"

class I_SongEntity;

class SongPlayer : public I_SongPlayer
{
    Q_OBJECT
public:
    explicit SongPlayer(I_SongEntity& songEntity);
    virtual ~SongPlayer();

    void play() override;
    void pause() override;
    void load(const QMediaContent& content) override;
    void changeVolume(int volume) override;

private slots:
    void updateSongPosition(qint64 pos);
    void songUpdate();

private:
    QScopedPointer<QMediaPlayer> mediaPlayer_;
    I_SongEntity& songEntity_;

};

