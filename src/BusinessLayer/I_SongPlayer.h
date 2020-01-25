#pragma once

#include<QObject>

class QMediaContent;
class I_SongPlayer : QObject
{
    Q_OBJECT
public:
    virtual ~I_SongPlayer();
    virtual void play() = 0;
    virtual void pause() = 0;
    virtual void load(const QMediaContent& content) = 0;
};
