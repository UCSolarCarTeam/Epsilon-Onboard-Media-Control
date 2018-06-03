#pragma once

#include <QWidget>
#include <QMediaMetaData>

enum MediaStatus
{
    NoMedia,
    Error
};
enum PlayerState
{
    Playing,
    Stopped,
    Paused
};

class I_MediaPlayer: public QObject
{
    Q_OBJECT

public:
    virtual qint64 position() = 0;
    virtual qint64 duration() = 0;
    virtual MediaStatus mediaStatus() = 0;
    virtual void setMedia(const QString& filePath) = 0;
    virtual void setVolume(int volume) = 0;
    virtual QString metaData(const QString& key) = 0;
    virtual PlayerState state() = 0;
    virtual void play() = 0;
    virtual void pause() = 0;
signals:
    void stateChanged();
    void durationChanged(qint64);
    void positionChanged(qint64);
    void metaDataAvailableChanged(bool);
};
