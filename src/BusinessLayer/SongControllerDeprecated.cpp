#include "SongControllerDeprecated.h"
#include "I_SongUrlSource.h"

#include <QTime>

SongControllerDeprecated::SongControllerDeprecated(I_SongUrlSource& songUrlSource) :
    index_(0),
    loop_(false),
    shuffle_(false),
    songList_(songUrlSource.getSongList())
{
}

QUrl SongControllerDeprecated::next()
{
    updateSongIndex_(1);
    return songList_[index_];
}

QUrl SongControllerDeprecated::prev()
{
    updateSongIndex_(-1);
    return songList_[index_];
}

void SongControllerDeprecated::updateSongIndex_(int step)
{
    if (shuffle_)
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

void SongControllerDeprecated::setShuffle(bool shuffle)
{
    shuffle_ = shuffle;
}

void SongControllerDeprecated::setLoop(bool loop)
{
    loop_ = loop;
}


