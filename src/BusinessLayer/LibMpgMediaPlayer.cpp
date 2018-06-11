#include "LibMpgMediaPlayer.h"
#include <ao/ao.h>
#include <mpg123.h>
#include <string>
#include <cstring>
#include <unistd.h>
#include <QDebug>

LibMpgMediaPlayer::LibMpgMediaPlayer(SongControl* songControl)
    : songControl_(songControl)
    , status_(MediaStatus::NoMedia)
    , state_(PlayerState::Playing)
{
    songplayer = new DeltaSongPlayer(songControl_);
    songplayer->StartThread();
}
void LibMpgMediaPlayer::play()
{
    state_ = PlayerState::Playing;
    songplayer->play();
}
void LibMpgMediaPlayer::pause()
{
    state_ = PlayerState::Paused;
    songplayer->pause();
}
qint64 LibMpgMediaPlayer::position()
{
    return songplayer->getCurrentTime() * 1000;
}
qint64 LibMpgMediaPlayer::duration()
{
    return songplayer->getSongLength() * 1000;
}
MediaStatus LibMpgMediaPlayer::mediaStatus()
{
    return status_;
}

PlayerState LibMpgMediaPlayer::state()
{
    return state_;
}

DeltaSongPlayer* LibMpgMediaPlayer::getDeltaSongPlayer()
{
    return songplayer;
}

void LibMpgMediaPlayer::setMedia(const QString& filePath)
{
    if(songplayer->loadSong(filePath) == 0)
    {
        status_ = MediaStatus::MediaLoaded;
    }
}
void LibMpgMediaPlayer::setVolume(int volume)
{
    this->volume = static_cast<double>(volume) / 100.0;
    songplayer->changeVolume(this->volume);

}
QString LibMpgMediaPlayer::metaData(const QString& key)
{
    if(key == QMediaMetaData::ContributingArtist)
    {
        return songplayer->currentSongArtist();
    }
    else if(key == QMediaMetaData::Title)
    {
        return songplayer->currentSongTitle();
    }
    else if(key == QMediaMetaData::AlbumTitle)
    {
        return songplayer->currentSongAlbum();
    }
    else
    {
        return "Ben is Fat";
    }
}
