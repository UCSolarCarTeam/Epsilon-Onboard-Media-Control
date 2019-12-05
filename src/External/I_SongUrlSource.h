#pragma once

class QUrl;
template<typename T> class QList;

class I_SongUrlSource
{
public:
    virtual ~I_SongUrlSource();
    virtual QList<QUrl> getSongList() = 0;
};
