#include "BusinessContainer.h"
#include "../DataLayer/DataContainer.h"
#include "SongPlayer/SongPlayer.h"

BusinessContainer::BusinessContainer(DataContainer& dataContainer)
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
