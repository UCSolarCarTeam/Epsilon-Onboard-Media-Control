#include "SongControlEntity.h"

SongControlEntity::SongControlEntity()
    : shuffle_(false)
    , loop_(false)
{
}

SongControlEntity::~SongControlEntity()
{
}

bool SongControlEntity::shuffle()
{
    return shuffle_;
}

void SongControlEntity::setShuffle(bool shuffle)
{
    shuffle_ = shuffle;
    emit controlStateChanged();
}

bool SongControlEntity::loop()
{
    return loop_;
}

void SongControlEntity::setLoop(bool loop)
{
    loop_ = loop;
    emit controlStateChanged();
}
