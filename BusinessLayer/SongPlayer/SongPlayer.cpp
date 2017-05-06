#include "SongPlayer.h"
#include "SongControl/SongControl.h"
#include "SongControl/SongControl.cpp"

namespace
{
const int MS_TO_MINUTES = 60000;
const double MS_TO_SECONDS = 1000.0;
const int PAGE_STEP_INCREMENTS = 10;
SongControl controller;
}

SongPlayer::SongPlayer(QWidget *parent) : QWidget(parent)
{
}

void SongPlayer::playFile(const QString &filePath)
{
//    playButton_->setEnabled(true);
//    infoLabel_->setText(QFileInfo(filePath).fileName());

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

void SongPlayer::openFile()
{
    const QStringList musicPaths = QStandardPaths::standardLocations(QStandardPaths::MusicLocation);
    const QString filePath =
        QFileDialog::getOpenFileName(this, tr("open file"),
                                     musicPaths.isEmpty() ? QDir::homePath() : musicPaths.first(),
                                     tr("mp3 files (*.mp3);;all files (*.*)"));
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
    const QString filePath = QString::fromStdString(controller.next_song());
    if(!filePath.isEmpty())
    {
       playFile(filePath);
    }
    else
    {
        qDebug() << "Warning filepath is empty";
    }
}

void SongPlayer::seekForward()
{
    positionSlider_->triggerAction(QSlider::SliderPageStepAdd);
}

void SongPlayer::seekBackward()
{
    positionSlider_->triggerAction(QSlider::SliderPageStepSub);
}

void SongPlayer::setPosition(int position)
{
    //avoid seeking when the slider value change is triggered fromupdatePosition()
    if(qAbs(mediaPlayer_.position() - position) > 99)
    {
        mediaPlayer_.setPosition(position);
    }
}

void SongPlayer::updatePosition(qint64 position)
{
    positionSlider_->setValue(position);

    QTime duration(0, position / MS_TO_MINUTES, qRound((position % MS_TO_MINUTES) / MS_TO_SECONDS));
    positionLabel_->setText(duration.toString(tr("mm:ss")));
}

void SongPlayer::updateDuration(qint64 duration)
{
    positionSlider_->setRange(0, duration);
    positionSlider_->setEnabled(duration > 0);
    positionSlider_->setPageStep(duration / PAGE_STEP_INCREMENTS);
}

void SongPlayer::updateInfo()
{
    QStringList info;
    QString author = mediaPlayer_.metaData("Author").toString();
    if(!author.isEmpty())
    {
        info += author;
    }
    QString title = mediaPlayer_.metaData("Title").toString();
    if(!title.isEmpty())
    {
        info += title;
    }
    if (!info.isEmpty())
    {
        infoLabel_->setText(info.join(tr(" - ")));
    }
}

void SongPlayer::handleError()
{
    playButton_->setEnabled(false);
    infoLabel_->setText(tr("Error: %1").arg(mediaPlayer_.errorString()));
}
