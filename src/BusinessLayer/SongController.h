#pragma once
#include "I_SongController.h"

#include <QList>
#include <QMediaPlaylist>

class I_SongUrlSource;
class QUrl;

class SongController : public I_SongController
{
public:
    SongController(I_SongUrlSource& songUrlSource);

    QUrl next();
    QUrl prev();
    void setShuffle(bool shuffle);
    void setLoop(bool loop);

private:
    void updateSongIndex_(int step);

    int index_;
    bool loop_;
    bool shuffle_;
    QMediaPlaylist playlist_;
    QList<QUrl> songList_;
};

