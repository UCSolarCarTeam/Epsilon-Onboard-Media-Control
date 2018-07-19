#include "LibMpgMediaPlayer.h"

LibMpgMediaPlayer::LibMpgMediaPlayer(SongControl* songControl)
    : songControl_(songControl)
    , status_(MediaStatus::NoMedia)
    , state_(PlayerState::Playing)
{
    songPlayer_ = new SongPlayerThread(songControl_);
    songPlayer_->StartThread();
}
void LibMpgMediaPlayer::play()
{
    state_ = PlayerState::Playing;
    songPlayer_->play();
}
void LibMpgMediaPlayer::pause()
{
    state_ = PlayerState::Paused;
    songPlayer_->pause();
}
qint64 LibMpgMediaPlayer::position()
{
    return songPlayer_->getCurrentTime() * 1000;
}
qint64 LibMpgMediaPlayer::duration()
{
    return songPlayer_->getSongLength() * 1000;
}
MediaStatus LibMpgMediaPlayer::mediaStatus()
{
    return status_;
}

PlayerState LibMpgMediaPlayer::state()
{
    return state_;
}

SongPlayerThread* LibMpgMediaPlayer::getSongPlayerThread()
{
    return songPlayer_;
}

void LibMpgMediaPlayer::setMedia(const QString& filePath)
{
    if (songPlayer_->loadSong(filePath) == 0)
    {
        status_ = MediaStatus::MediaLoaded;
    }
}
void LibMpgMediaPlayer::setVolume(int volume)
{
    this->volume_ = static_cast<double>(volume) / 100.0;
    songPlayer_->changeVolume(this->volume_);

}
QString LibMpgMediaPlayer::metaData(const QString& key)
{
    if (key == QMediaMetaData::ContributingArtist)
    {
        return songPlayer_->currentSongArtist();
    }
    else if (key == QMediaMetaData::Title)
    {
        return songPlayer_->currentSongTitle();
    }
    else if (key == QMediaMetaData::AlbumTitle)
    {
        return songPlayer_->currentSongAlbum();
    }
    else
    {
        return "Metadata Unavailable";
    }
}
