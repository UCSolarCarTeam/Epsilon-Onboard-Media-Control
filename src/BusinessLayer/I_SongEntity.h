#pragma once

#include <QObject>

class QMediaContent;

class I_SongEntity : public QObject
{
    Q_OBJECT
public:
    virtual ~I_SongEntity();
    virtual QImage image() = 0;
    virtual QString artist() = 0;
    virtual QString songName() = 0;
    virtual qint64 duration() = 0;
    virtual qint64 position() = 0;

    virtual void setImage(QImage image) = 0;
    virtual void setArtist(QString artist) = 0;
    virtual void setSongName(QString songName) = 0;
    virtual void setDuration(qint64 duration) =0;
    virtual void setPosition(qint64 position) =0;

signals:
    void songChanged();
    void positionChanged();
};
