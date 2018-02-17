#include "SongPlayer.h"

namespace
{
    const int MS_TO_MINUTES = 60000;
    const double MS_TO_SECONDS = 1000.0;
    const int PAGE_STEP_INCREMENTS = 10;
}

SongPlayer::SongPlayer(QWidget* parent) : QWidget(parent)
  , controller_(new SongControl())
  , shuffle_(false)
  , loop_(false)
{
    connect(&mediaPlayer_, &QMediaPlayer::stateChanged, this, &SongPlayer::updateState);
    connect(&mediaPlayer_, SIGNAL(durationChanged(qint64)), this, SLOT(durationChanged(qint64)));
    connect(&mediaPlayer_, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    connect(&mediaPlayer_, SIGNAL(metaDataAvailableChanged(bool)), this, SLOT(updateInfo()));
}

SongPlayer::~SongPlayer()
{
}

void SongPlayer::updateState()
{
    if (mediaPlayer_.position() >= mediaPlayer_.duration() && mediaPlayer_.duration() != -1)
    {
         playNext();
    }
}

void SongPlayer::openFile()
{
    const QString filePath = controller_->currentSong();

    if (!filePath.isEmpty())
    {
        setFile(filePath);
    }
    else
    {
        qDebug() << "File path is empty";
    }
}

void SongPlayer::openNext()
{
    const QString filePath = controller_->nextSong();

    if (!filePath.isEmpty())
    {
        setFile(filePath);
    }
    else
    {
        qDebug() << "Warning filepath is empty";
    }
}

void SongPlayer::playNext()
{
    if(loop_)
    {
        openFile();
    }
    else if (shuffle_)
    {
        openShuffle();
    }
    else
    {
        openNext();
    }

    togglePlayback();
}

void SongPlayer::openPrevious()
{
    const QString filePath = controller_->previousSong();

    if (!filePath.isEmpty())
    {
        setFile(filePath);
    }
    else
    {
        qDebug() << "Warning filepath is empty";
    }
}

void SongPlayer::openShuffle()
{
    const QString filePath = controller_->shuffleSong();

    if (!filePath.isEmpty())
    {
        setFile(filePath);
    }
    else
    {
        qDebug() << "Warning filepath is empty";
    }
}

void SongPlayer::playPrevious()
{
    if(shuffle_)
    {
        openShuffle();
    }
    else
    {
        openPrevious();
    }
    togglePlayback();
}

void SongPlayer::togglePlayback()
{
    if (mediaPlayer_.mediaStatus() == QMediaPlayer::NoMedia)
    {
        if(shuffle_)
        {
            openShuffle();
        }
        else
        {
            openFile();
        }
        mediaPlayer_.play();
    }
    else if (mediaPlayer_.state() == QMediaPlayer::PlayingState)
    {
        mediaPlayer_.pause();
    }
    else
    {
        mediaPlayer_.play();
    }
}

void SongPlayer::setFile(const QString& filePath)
{
    mediaPlayer_.setMedia(QUrl::fromLocalFile(filePath));
}

void SongPlayer::durationChanged(qint64 duration)
{
    duration_ = duration;
}

void SongPlayer::positionChanged(qint64 position)
{
    position_ = position;
    emit updateProgress(position_, duration_);
}

void SongPlayer::adjustVolume(int volume)
{
    mediaPlayer_.setVolume(volume);
}

void SongPlayer::toggleShuffle()
{
    if(shuffle_)
    {
        shuffle_ = false;
    }
    else
    {
        shuffle_ = true;
    }
}

void SongPlayer::toggleLoop()
{
    if(loop_)
    {
        loop_ = false;
    }
    else
    {
        loop_ = true;
    }
}

void SongPlayer::updateInfo()
{
    artist_ = mediaPlayer_.metaData(QMediaMetaData::ContributingArtist).toString();
    title_ = mediaPlayer_.metaData(QMediaMetaData::Title).toString();
    cover_ = mediaPlayer_.metaData(QMediaMetaData::CoverArtImage).value<QImage>();
    emit updateGUI(title_, artist_);
}
