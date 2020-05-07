#pragma once

#include <QList>

#include "I_SongUrlSource.h"

class LocalSongUrlSource : public I_SongUrlSource
{
public:
    explicit LocalSongUrlSource();
    virtual ~LocalSongUrlSource();

    QList<QUrl> getSongList();

private:
    void loadSongs();

    QList<QUrl> songList_;
};
