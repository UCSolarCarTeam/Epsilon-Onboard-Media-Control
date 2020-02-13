#pragma once

#include "I_SongControlEntity.h"

class SongControlEntity :  public I_SongControlEntity
{
    Q_OBJECT
public:
    explicit SongControlEntity();
    virtual ~SongControlEntity();

    bool shuffle() override;
    void setShuffle(bool shuffle) override;

    bool loop() override;
    void setLoop(bool loop) override;

    bool playing() override;
    void setPlaying(bool playing) override;

    int volume() override;
    void setVolume(int volume) override;

signals:
    void controlStateChanged() override;
    void playingStateChanged() override;

private:
    bool shuffle_;
    bool loop_;
    bool playing_;
    int volume_;

};
