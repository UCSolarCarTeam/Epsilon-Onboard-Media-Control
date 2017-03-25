#include "BusinessContainer.h"
#include "../DataLayer/DataContainer.h"

BusinessContainer::BusinessContainer()
    : songPlayer_(new SongPlayer())
{
}

BusinessContainer::~BusinessContainer()
{
}

SongPlayer& BusinessContainer::SongPlayer()
{
    return *songPlayer_;
}
