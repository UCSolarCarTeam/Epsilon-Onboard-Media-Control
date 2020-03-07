#pragma once

#include <QObject>

class I_SongController : public QObject
{
    Q_OBJECT
public:
    virtual ~I_SongController() {}

    virtual void playNext() = 0;
    virtual void playPrevious() = 0;
};
