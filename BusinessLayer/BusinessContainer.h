#pragma once

#include <QScopedPointer>

class BusinessContainerPrivate;
class SongPlayer;

class BusinessContainer
{
public:
    explicit BusinessContainer();
    ~BusinessContainer();
    SongPlayer& songPlayer();

private:
    QScopedPointer<SongPlayer> songPlayer_;
};
