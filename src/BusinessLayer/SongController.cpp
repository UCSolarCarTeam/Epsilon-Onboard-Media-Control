#include "SongController.h"
#include "I_SongUrlSource.h"

#include <QTime>

SongController::SongController(I_SongUrlSource& songUrlSource) : songList_(songUrlSource.getSongList()), index_(0)
{
}

QUrl SongController::next()
{
    updateSongIndex_(1);
    return songList_[index_];
}

QUrl SongController::prev()
{
    updateSongIndex_(-1);
    return songList_[index_];
}

void SongController::updateSongIndex_(int step)
{
    if(shuffle_)
    {
        qsrand(static_cast<uint>(QDateTime::currentMSecsSinceEpoch() / 1000));
        index_ = qrand() % songList_.size();
    }
    else if (!loop_)
    {
        index_ += step;
        index_ %= songList_.size();
    }
}

void SongController::setShuffle(bool shuffle)
{
    shuffle_ = shuffle;
}

void SongController::setLoop(bool loop)
{
    loop_ = loop;
}


