#include <QImage>
#include <QMediaMetaData>

#include "I_SongState.h"
#include "SongPlayer.h"

SongPlayer::SongPlayer(I_SongState& songState):
    mediaPlayer_(new QMediaPlayer()),
    songState_(songState)
{
    connect(mediaPlayer_.data(), SIGNAL(positionChanged(qint64)), this, SLOT(updateSongPosition(qint64)));
    connect(mediaPlayer_.data(), SIGNAL(durationChanged(qint64)), this, SLOT(updateSongDuration(qint64)));
    connect(mediaPlayer_.data(), SIGNAL(metaDataAvailableChanged(bool)), this, SLOT(updateSong()));
    connect(mediaPlayer_.data(), SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)));
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
    songState_.setPosition(pos);
}

void SongPlayer::updateSongDuration(qint64 pos)
{
    songState_.setDuration(pos);
}

void SongPlayer::updateSong()
{
    songState_.setImage(mediaPlayer_->metaData(QMediaMetaData::CoverArtImage).value<QImage>());
    songState_.setArtist(mediaPlayer_->metaData(QMediaMetaData::ContributingArtist).toString());
    songState_.setSongName(mediaPlayer_->metaData(QMediaMetaData::Title).toString());
}

void SongPlayer::changeVolume(const int volume)
{
    mediaPlayer_->setVolume(volume);
}
