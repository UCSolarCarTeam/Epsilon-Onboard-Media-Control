#pragma once

class QUrl;

class I_SongControllerDeprecated
{
public:
    virtual ~I_SongControllerDeprecated();
    virtual QUrl next() = 0;
    virtual QUrl prev() = 0;
    virtual void setShuffle(bool shuffle) = 0;
    virtual void setLoop(bool loop) = 0;
};
