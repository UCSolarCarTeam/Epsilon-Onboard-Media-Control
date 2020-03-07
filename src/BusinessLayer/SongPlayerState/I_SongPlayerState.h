#pragma once

#include <QObject>

class I_SongPlayerState : public QObject
{
    Q_OBJECT
public:
    virtual ~I_SongPlayerState() {}

    virtual bool shuffle() = 0;
    virtual void setShuffle(bool shuffle) = 0;

    virtual bool loop() = 0;
    virtual void setLoop(bool loop) = 0;

    virtual bool playing() = 0;
    virtual void setPlaying(bool playing) = 0;

    virtual int volume() = 0;
    virtual void setVolume(int volume) = 0;

signals:
    void controlStateChanged();
    void playingStateChanged();
    void volumeStateChanged();
};
