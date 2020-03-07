#pragma once

#include "I_SongState.h"

#include <QImage>

class SongState : public I_SongState
{
    Q_OBJECT
public:
    explicit SongState();
    virtual ~SongState();

public:
    QImage image() override;
    QString artist() override;
    QString songName() override;
    qint64 duration() override;
    qint64 position() override;

    void setImage(QImage image) override;
    void setArtist(QString artist) override;
    void setSongName(QString songName) override;
    void setDuration(qint64 duration) override;
    void setPosition(qint64 position) override;

private:
    QImage image_;
    QString artist_;
    QString songName_;
    qint64 duration_;
    qint64 position_;
};
