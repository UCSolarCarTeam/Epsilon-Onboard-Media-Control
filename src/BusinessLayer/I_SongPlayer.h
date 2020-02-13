#pragma once

#include<QObject>

class QMediaContent;
class I_SongPlayer : public QObject
{
    Q_OBJECT
public:
    virtual ~I_SongPlayer(){}
    virtual void play() = 0;
    virtual void pause() = 0;
    virtual void load(const QMediaContent& content) = 0;

public slots:
    //slots
    virtual void updateSongPosition(qint64 pos) = 0;
    virtual void songUpdate(const QMediaContent&) = 0;
};
