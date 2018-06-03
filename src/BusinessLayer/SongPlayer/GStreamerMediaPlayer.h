#pragma once
#include <QMediaPlayer>
#include "I_MediaPlayer.h"

class GStreamerMediaPlayer : public I_MediaPlayer
{
    Q_OBJECT
public:
    GStreamerMediaPlayer();
    qint64 position();
    qint64 duration();
    MediaStatus mediaStatus();
    void setMedia(const QString& filePath);
    void setVolume(int volume);
    QString metaData(const QString& key);
    void play();
    void pause();
    PlayerState state();

signals:
    void stateChanged();
    void durationChanged(qint64);
    void positionChanged(qint64);
    void metaDataAvailableChanged(bool);

private:
    QMediaPlayer mediaPlayer_;
};
