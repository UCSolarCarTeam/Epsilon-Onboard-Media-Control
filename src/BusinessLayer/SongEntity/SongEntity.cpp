#include "SongEntity.h"

SongEntity::SongEntity()
{}

SongEntity::~SongEntity()
{
}

QImage SongEntity::image()
{
    return image_;
}

QString SongEntity::artist()
{
    return artist_;
}

QString SongEntity::songName()
{
    return songName_;
}

qint64 SongEntity::duration()
{
    return duration_;
}

qint64 SongEntity::position()
{
    return position_;
}

void SongEntity::setImage(QImage image)
{
    image_ = image;
    emit metaDataChanged();
}

void SongEntity::setArtist(QString artist)
{
    artist_ = artist;
    emit metaDataChanged();
}

void SongEntity::setSongName(QString songName)
{
    songName_ = songName;
    emit metaDataChanged();
}

void SongEntity::setDuration(qint64 duration)
{
    duration_ = duration;
    emit durationChanged();
}

void SongEntity::setPosition(qint64 position)
{
    position_ = position;
    emit positionChanged();
}
