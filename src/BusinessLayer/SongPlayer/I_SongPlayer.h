#pragma once

#include <QMediaPlayer>
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
    virtual void changeVolume(int volume) = 0;

signals:
    void mediaStatusChanged(QMediaPlayer::MediaStatus);
};
