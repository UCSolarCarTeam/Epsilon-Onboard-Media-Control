#include "SongPlayer.h"
#include "I_SongEntity.h"

#include <QImage>
#include <QMediaMetaData>

SongPlayer::SongPlayer(I_SongEntity& songEntity):
    mediaPlayer_(new QMediaPlayer()),
    songEntity_(songEntity)
{}

void SongPlayer::play()
{
    mediaPlayer_->play();
}

void SongPlayer::pause()
{
    mediaPlayer_->pause();
}

void SongPlayer::load(const QMediaContent &content)
{
    mediaPlayer_->setMedia(content);

    songEntity_.setDuration(mediaPlayer_->duration());
    songEntity_.setImage(mediaPlayer_->metaData(QMediaMetaData::CoverArtImage).value<QImage>());
    songEntity_.setArtist(mediaPlayer_->metaData(QMediaMetaData::ContributingArtist).toString());
    songEntity_.setSongName(mediaPlayer_->metaData(QMediaMetaData::Title).toString());
}
