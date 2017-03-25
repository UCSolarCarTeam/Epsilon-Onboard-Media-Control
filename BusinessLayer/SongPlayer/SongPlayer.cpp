#include "SongPlayer.h"
#include "SongControl/SongControl.h"
#include "SongControl/SongControl.cpp"

namespace
{
const int MS_TO_MINUTES = 60000;
const double MS_TO_SECONDS = 1000.0;
const int PAGE_STEP_INCREMENTS = 10;
}

SongPlayer::SongPlayer(QWidget *parent) : QWidget(parent)
{
}

void SongPlayer::playFile(const QString &filePath)
{
    playButton_->setEnabled(true);
    infoLabel_->setText(QFileInfo(filePath).fileName());

    mediaPlayer_.setMedia(QUrl::fromLocalFile(filePath));
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
    if (state == QMediaPlayer::PlayingState)
    {
        playButton_->setToolTip(tr("Pause"));
       // playButton_->setIcon(Style()->standardIcon(QStyle::SP_MediaPause));
    }
    else
    {
        playButton_->setToolTip(tr("Play"));
        playButton_->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    }
    if (mediaPlayer_.position() >= mediaPlayer_.duration() && mediaPlayer_.duration() != -1)
    {
        openNext();
        togglePlayback();
    }
}
