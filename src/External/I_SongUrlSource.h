#pragma once

class QUrl;
template<typename T> class QList;

class I_SongURLSource
{
public:
    virtual ~I_SongURLSource();
    virtual QList<QUrl> getSongList() = 0;
};
