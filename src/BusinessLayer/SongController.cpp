#include "SongController.h"

#include "I_SongControlEntity.h"
#include "I_SongPlayer.h"

#include <I_SongUrlSource.h>
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
    if (!previousSongs_->isEmpty())
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

void SongController::loadSong()
{
    if (!songUrls_.isEmpty())
    {
        previousSongs_->push(songIndex_);
        songPlayer_.load(QMediaContent(songUrls_[songIndex_]));
    }
}
