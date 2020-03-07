#include "SongPlayerState.h"

SongPlayerState::SongPlayerState()
    : shuffle_(false)
    , loop_(false)
    , playing_(false)
    , volume_(100)
{
}

SongPlayerState::~SongPlayerState()
{
}

bool SongPlayerState::shuffle()
{
    return shuffle_;
}

void SongPlayerState::setShuffle(bool shuffle)
{
    if (shuffle_ != shuffle)
    {
        if (loop_)
        {
            loop_ = false;
        }

        shuffle_ = shuffle;
        emit controlStateChanged();
    }
}

bool SongPlayerState::loop()
{
    return loop_;
}

void SongPlayerState::setLoop(bool loop)
{
    if (loop_ != loop)
    {
        if (shuffle_)
        {
            shuffle_ = false;
        }

        loop_ = loop;
        emit controlStateChanged();
    }
}

bool SongPlayerState::playing()
{
    return playing_;
}

void SongPlayerState::setPlaying(bool playing)
{
    if (playing_ != playing)
    {
        playing_ = playing;
        emit playingStateChanged();
    }
}

int SongPlayerState::volume()
{
    return volume_;
}

void SongPlayerState::setVolume(int volume)
{
    if (volume_ != volume)
    {
        volume_ = volume;
        emit volumeStateChanged();
    }
}
