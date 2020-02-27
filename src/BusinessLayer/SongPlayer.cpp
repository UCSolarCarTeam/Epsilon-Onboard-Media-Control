#include "SongPlayer.h"

#include "I_SongEntity.h"
#include <QImage>
#include <QMediaMetaData>

SongPlayer::SongPlayer(I_SongEntity& songEntity):
    mediaPlayer_(new QMediaPlayer()),
    songEntity_(songEntity)
{
    connect(mediaPlayer_.data(), SIGNAL(positionChanged(qint64)), this, SLOT(updateSongPosition(qint64)));
    connect(mediaPlayer_.data(), SIGNAL(mediaChanged(const QMediaContent&)), this, SLOT(songUpdate(const QMediaContent&)));
}

SongPlayer::~SongPlayer()
{
}

void SongPlayer::play()
{
    mediaPlayer_->play();
}

void SongPlayer::pause()
{
    mediaPlayer_->pause();
}

void SongPlayer::load(const QMediaContent& content)
{
    mediaPlayer_->setMedia(content);
}

void SongPlayer::updateSongPosition(qint64 pos)
{
    songEntity_.setPosition(pos);
}

void SongPlayer::songUpdate(const QMediaContent&)
{
    songEntity_.setDuration(mediaPlayer_->duration());
    songEntity_.setImage(mediaPlayer_->metaData(QMediaMetaData::CoverArtImage).value<QImage>());
    songEntity_.setArtist(mediaPlayer_->metaData(QMediaMetaData::ContributingArtist).toString());
    songEntity_.setSongName(mediaPlayer_->metaData(QMediaMetaData::Title).toString());
    emit songEntity_.metaDataChanged();
}


void SongPlayer::changeVolume(int volume)
{
    mediaPlayer_->setVolume(volume);
}
