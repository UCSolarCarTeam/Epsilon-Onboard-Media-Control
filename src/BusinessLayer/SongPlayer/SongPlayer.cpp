#include "SongPlayer.h"

#include "I_SongEntity.h"
#include <QImage>
#include <QMediaMetaData>

SongPlayer::SongPlayer(I_SongEntity& songEntity):
    mediaPlayer_(new QMediaPlayer()),
    songEntity_(songEntity)
{
    connect(mediaPlayer_.data(), SIGNAL(positionChanged(qint64)), this, SLOT(updateSongPosition(qint64)));
    connect(mediaPlayer_.data(), SIGNAL(durationChanged(qint64)), this, SLOT(updateSongDuration(qint64)));
    connect(mediaPlayer_.data(), SIGNAL(metaDataAvailableChanged(bool)), this, SLOT(songUpdate()));
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

void SongPlayer::updateSongDuration(qint64 pos)
{
    songEntity_.setDuration(pos);
}

void SongPlayer::songUpdate()
{
    songEntity_.setImage(mediaPlayer_->metaData(QMediaMetaData::CoverArtImage).value<QImage>());
    songEntity_.setArtist(mediaPlayer_->metaData(QMediaMetaData::ContributingArtist).toString());
    songEntity_.setSongName(mediaPlayer_->metaData(QMediaMetaData::Title).toString());
}


void SongPlayer::changeVolume(int volume)
{
    mediaPlayer_->setVolume(volume);
}
