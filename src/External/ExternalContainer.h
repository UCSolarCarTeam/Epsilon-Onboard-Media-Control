#pragma once

#include <QScopedPointer>

class I_SongUrlSource;

class ExternalContainer
{
public:
    explicit ExternalContainer();
    ~ExternalContainer();

public:
    I_SongUrlSource& localSongUrlSource();

private:
    QScopedPointer<I_SongUrlSource> localSongUrlSource_;
};
