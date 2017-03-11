#include "SongPlayer.h"

namespace
{
const int MS_TO_MINUTES = 60000;
const double MS_TO_SECONDS = 1000.0;
const int PAGE_STEP_INCREMENTS = 10;
}

SongPlayer::SongPlayer(QWidget *parent) : QWidget(parent)
{
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

void SongPlayer::playFile(const QString &filePath)
{
    playButton_->setEnabled(true);
    infoLabel_->setText(QFileInfo(filePath).fileName());

    mediaPlayer_.setMedia(QUrl::fromLocalFile(filePath));
    mediaPlayer_.play();
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
