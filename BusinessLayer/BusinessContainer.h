#pragma once

#include <QScopedPointer>

class DataContainer;
class BusinessContainerPrivate;
class SongPlayer;

class BusinessContainer
{
public:
    explicit BusinessContainer(DataContainer& dataContainer);
    ~BusinessContainer();
    SongPlayer& songPlayer();

private:
    QScopedPointer<SongPlayer> songPlayer_;
};
