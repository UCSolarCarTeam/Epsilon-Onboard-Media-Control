#include <QMediaContent>
#include <QRandomGenerator>
#include <QStack>

#include "I_SongPlayer.h"
#include "I_SongPlayerState.h"
#include "I_SongUrlSource.h"
#include "SongController.h"

SongController::SongController(I_SongPlayer& songPlayer,
                               I_SongPlayerState& songPlayerState,
                               I_SongUrlSource& songUrlSource)
    : songPlayer_(songPlayer)
    , songPlayerState_(songPlayerState)
    , songUrls_(songUrlSource.getSongList())
    , songIndex_(0)
    , generator_(QRandomGenerator::system())
    , previousSongs_(new QStack<int>)
{
    connect(&songPlayerState_, SIGNAL(playingStateChanged()), this, SLOT(toggleSongPlayingState()));
    connect(&songPlayerState_, SIGNAL(volumeStateChanged()), this, SLOT(changeVolumeState()));
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

    previousSongs_->push(songIndex_);

    if (songPlayerState_.loop())
    {
        songPlayer_.load(QMediaContent(songUrls_[songIndex_]));
    }
    else if (songPlayerState_.shuffle())
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
    if (!songPlayerState_.loop() && !previousSongs_->isEmpty())
    {
        songIndex_ = previousSongs_->pop();
    }

    loadSong();
}

void SongController::toggleSongPlayingState()
{
    if (songPlayerState_.playing())
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
    songPlayer_.changeVolume(songPlayerState_.volume());
}

void SongController::checkSongEnded(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::EndOfMedia)
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
