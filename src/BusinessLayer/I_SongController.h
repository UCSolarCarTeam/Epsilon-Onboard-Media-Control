#pragma once

class QUrl;

class I_SongController
{
public:
    virtual ~I_SongController();
    virtual QUrl next() = 0;
    virtual QUrl prev() = 0;
    virtual void setShuffle(bool shuffle) = 0;
    virtual void setLoop(bool loop) = 0;
};
