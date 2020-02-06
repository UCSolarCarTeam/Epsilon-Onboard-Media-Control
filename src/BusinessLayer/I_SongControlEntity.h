#include <QObject>

#pragma once

class I_SongControlEntity : public QObject
{
    Q_OBJECT
public:
    virtual ~I_SongControlEntity(){}

    virtual bool shuffle() = 0;
    virtual void setShuffle(bool shuffle) = 0;

    virtual bool loop() = 0;
    virtual void setLoop(bool loop) = 0;

    virtual bool playing() = 0;
    virtual void setPlaying(bool play) = 0;

// signals
protected:
    virtual void controlStateChanged() = 0;
    virtual void playingStateChanged() = 0;
};
