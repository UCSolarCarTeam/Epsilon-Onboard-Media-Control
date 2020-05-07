#include "SongState.h"

SongState::SongState()
{}

SongState::~SongState()
{
}

QImage SongState::image()
{
    return image_;
}

QString SongState::artist()
{
    return artist_;
}

QString SongState::songName()
{
    return songName_;
}

qint64 SongState::duration()
{
    return duration_;
}

qint64 SongState::position()
{
    return position_;
}

void SongState::setImage(QImage image)
{
    image_ = image;
    emit metaDataChanged();
}

void SongState::setArtist(QString artist)
{
    artist_ = artist;
    emit metaDataChanged();
}

void SongState::setSongName(QString songName)
{
    songName_ = songName;
    emit metaDataChanged();
}

void SongState::setDuration(qint64 duration)
{
    duration_ = duration;
    emit durationChanged();
}

void SongState::setPosition(qint64 position)
{
    position_ = position;
    emit positionChanged();
}
