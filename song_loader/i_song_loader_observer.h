#ifndef I_SONG_LOADER_OBSERVER_H
#define I_SONG_LOADER_OBSERVER_H
#include <vector>
#pragma once

class I_SongLoaderObserver
{
public:
    virtual void current_song(std::string song_path) = 0;
};

#endif // I_SONG_LOADER_OBSERVER_H

