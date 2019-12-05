#pragma once

#include <QObject>

class QUrl;

class SongEntity : public QObject
{
    Q_OBJECT
public:
    virtual ~SongEntity();
    virtual QImage image() = 0;
    virtual QString artist() = 0;
    virtual QString songName() = 0;
    virtual qint64 duration() = 0;
    virtual qint64 position() = 0;
    virtual QUrl songUrl() = 0;

    virtual QImage setImage() = 0;
    virtual QString setArtist() = 0;
    virtual QString setSongName() = 0;
    virtual qint64 setDuration() =0;
    virtual qint64 setPosition() =0;
    virtual QUrl setSongUrl() = 0;

signals:
    void songChanged();
    void positionChanged();
};
