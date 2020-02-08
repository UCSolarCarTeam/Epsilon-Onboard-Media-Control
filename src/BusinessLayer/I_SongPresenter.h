#pragma once

#include <QObject>

class QUrl;

class SongPresenter : public QObject
{
    Q_OBJECT
public:
    virtual ~SongPresenter();
    virtual QImage image() = 0;
    virtual QString artist() = 0;
    virtual QString songName() = 0;
    virtual qint64 duration() = 0;
    virtual qint64 position() = 0;

signals:
    void songChanged();
    void positionChanged();
};
