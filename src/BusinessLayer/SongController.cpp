#include "SongController.h"

#include "I_SongControlEntity.h"
#include "I_SongPlayer.h"

#include <QMediaContent>
#include <QRandomGenerator>
#include <QStack>

SongController::SongController(I_SongPlayer &songPlayer, I_SongControlEntity &songControlEntity,
                               QList<QUrl> &songUrls)
    : songPlayer_(songPlayer)
    , songControlEntity_(songControlEntity)
    , songUrls_(songUrls)
    , songIndex_(0)
    , generator_(QRandomGenerator::system())
    , previousSongs_(new QStack<int>)
{
}

SongController::~SongController()
{
}

void SongController::playNext()
{
    if(songUrls_.size() == 0)
    {
        return;
    }
    if(songControlEntity_.loop())
    {
        songPlayer_.load(QMediaContent(songUrls_[songIndex_]));
    }
    else if(songControlEntity_.shuffle())
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
    if(!previousSongs_->isEmpty())
    {
        songIndex_ = previousSongs_->pop();
    }
    loadSong();
}

void SongController::loadSong()
{
    previousSongs_->push(songIndex_);
    songPlayer_.load(QMediaContent(songUrls_[songIndex_]));
}
