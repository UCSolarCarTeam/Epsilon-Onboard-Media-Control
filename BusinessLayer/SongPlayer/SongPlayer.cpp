#include "SongPlayer.h"

namespace
{
    const int MS_TO_MINUTES = 60000;
    const double MS_TO_SECONDS = 1000.0;
    const int PAGE_STEP_INCREMENTS = 10;
}

SongPlayer::SongPlayer(QWidget* parent) : QWidget(parent)
{
    SongControl controller_;
    connect(&mediaPlayer_, &QMediaPlayer::stateChanged, this, &SongPlayer::updateState);
    connect(&mediaPlayer_, SIGNAL(durationChanged(qint64)), this, SLOT(durationChanged(qint64)));
    connect(&mediaPlayer_, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
}

void SongPlayer::playFile(const QString& filePath)
{
    mediaPlayer_.setMedia(QUrl::fromLocalFile(filePath));
    emit updateTitle(filePath);
}

void SongPlayer::togglePlayback()
{
    if (mediaPlayer_.mediaStatus() == QMediaPlayer::NoMedia)
    {
        openFile();
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

void SongPlayer::updateState(QMediaPlayer::State state)
{
    if (mediaPlayer_.position() >= mediaPlayer_.duration() && mediaPlayer_.duration() != -1)
    {
        playNext();
    }

    emit mediaPlayer_.durationChanged(mediaPlayer_.duration());
}

void SongPlayer::openFile()
{
    const QString filePath = controller_.currentSong();

    if (!filePath.isEmpty())
    {
        playFile(filePath);
    }
    else
    {
        qDebug() << "File path is empty";
    }
}

void SongPlayer::openNext()
{
    const QString filePath = controller_.nextSong();

    if (!filePath.isEmpty())
    {
        playFile(filePath);
    }
    else
    {
        qDebug() << "Warning filepath is empty";
    }
}

void SongPlayer::openPrevious()
{
    const QString filePath = controller_.previousSong();

    if (!filePath.isEmpty())
    {
        playFile(filePath);
    }
    else
    {
        qDebug() << "Warning filepath is empty";
    }
}

void SongPlayer::playNext()
{
    openNext();
    togglePlayback();
}

void SongPlayer::playPrevious()
{
    openPrevious();
    togglePlayback();
}

void SongPlayer::durationChanged(qint64 duration)
{
    emit updateDuration(duration);
}

void SongPlayer::positionChanged(qint64 position)
{
    emit updatePosition(position);
}



void SongPlayer::handleError()
{
    playButton_->setEnabled(false);
    infoLabel_->setText(tr("Error: %1").arg(mediaPlayer_.errorString()));
}
