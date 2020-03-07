#pragma once

#include "I_SongPlayerState.h"

class SongPlayerState :  public I_SongPlayerState
{
    Q_OBJECT
public:
    explicit SongPlayerState();
    virtual ~SongPlayerState();

    bool shuffle() override;
    void setShuffle(bool shuffle) override;

    bool loop() override;
    void setLoop(bool loop) override;

    bool playing() override;
    void setPlaying(bool playing) override;

    int volume() override;
    void setVolume(int volume) override;

private:
    bool shuffle_;
    bool loop_;
    bool playing_;
    int volume_;

};
