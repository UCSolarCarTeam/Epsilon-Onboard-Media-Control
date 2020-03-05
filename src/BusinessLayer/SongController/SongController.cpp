#include "SongController.h"

#include "I_SongControlEntity.h"
#include "I_SongPlayer.h"

#include "I_SongUrlSource.h"
#include <QMediaContent>
#include <QRandomGenerator>
#include <QStack>

SongController::SongController(I_SongPlayer& songPlayer, I_SongControlEntity& songControlEntity,
                               I_SongUrlSource& songUrlSource)
    : songPlayer_(songPlayer)
    , songControlEntity_(songControlEntity)
    , songUrls_(songUrlSource.getSongList())
    , songIndex_(0)
    , generator_(QRandomGenerator::system())
    , previousSongs_(new QStack<int>)
{
    connect(&songControlEntity_, SIGNAL(playingStateChanged()), this, SLOT(toggleSongPlayingState()));
    connect(&songControlEntity_, SIGNAL(volumeStateChanged()), this, SLOT(changeVolumeState()));
    connect(&songPlayer_, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(checkSongEnded(QMediaPlayer::MediaStatus)));
    loadSong();
}

SongController::~SongController()
{
}

void SongController::playNext()
{
    if (songUrls_.size() == 0)
    {
        return;
    }
    //Add the current song to previously played songs
    previousSongs_->push(songIndex_);

    if (songControlEntity_.loop())
    {
        songPlayer_.load(QMediaContent(songUrls_[songIndex_]));
    }
    else if (songControlEntity_.shuffle())
    {
        songIndex_ = generator_->bounded(songUrls_.size());
    }
    else
    {
        ++songIndex_ %= songUrls_.size();
    }
    loadSong();
}

void SongController::playPrevious()
{
    if (!songControlEntity_.loop() && !previousSongs_->isEmpty())
    {
        songIndex_ = previousSongs_->pop();
    }

    loadSong();
}

void SongController::toggleSongPlayingState()
{
    if (songControlEntity_.playing())
    {
        songPlayer_.play();
    }
    else
    {
        songPlayer_.pause();
    }
}

void SongController::changeVolumeState()
{
    songPlayer_.changeVolume(songControlEntity_.volume());
}

void SongController::checkSongEnded(QMediaPlayer::MediaStatus status)
{
    if(status == QMediaPlayer::EndOfMedia)
    {
        playNext();
    }
}

void SongController::loadSong()
{
    if (!songUrls_.isEmpty())
    {
        songPlayer_.load(QMediaContent(songUrls_[songIndex_]));
        toggleSongPlayingState();
    }
}
