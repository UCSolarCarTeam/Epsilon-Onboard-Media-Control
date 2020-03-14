#include "ExternalContainer.h"
#include "LocalSongUrlSource.h"

ExternalContainer::ExternalContainer()
    : localSongUrlSource_(new LocalSongUrlSource())
{
}

ExternalContainer::~ExternalContainer()
{
}

I_SongUrlSource& ExternalContainer::localSongUrlSource()
{
    return *localSongUrlSource_;
}
