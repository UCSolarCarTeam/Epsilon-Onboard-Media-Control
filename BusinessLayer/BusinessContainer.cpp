#include "BusinessContainer.h"
#include "SongPlayer/SongPlayer.h"

BusinessContainer::BusinessContainer()
    : songPlayer_(new SongPlayer())
{
}

BusinessContainer::~BusinessContainer()
{
}

SongPlayer& BusinessContainer::songPlayer()
{
    return *songPlayer_;
}
