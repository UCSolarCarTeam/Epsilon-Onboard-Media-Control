#include "SongPlayer.h"

namespace
{
    const int MS_TO_MINUTES = 60000;
    const double MS_TO_SECONDS = 1000.0;
    const int MIN_LIGHT = 40;
    const int SKIP_PIXELS = 10;
    const int PAGE_STEP_INCREMENTS = 10;
    const QString ALBUM_FILE_PATH = QDir::homePath() + "/Pictures/Covers/";
}

SongPlayer::SongPlayer(QWidget* parent) : QWidget(parent)
    , controller_(new SongControl())
    , shuffle_(false)
    , loop_(false)
    , mediaPlayer_(new LibMpgMediaPlayer(controller_.data()))
{
    connect(mediaPlayer_.data(), SIGNAL(stateChanged()), this, SLOT(updateState()));
    connect(mediaPlayer_.data()->getDeltaSongPlayer(), SIGNAL(durationChanged(qint64)), this, SLOT(durationChanged(qint64)));
    connect(mediaPlayer_.data()->getDeltaSongPlayer(), SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    connect(mediaPlayer_.data()->getDeltaSongPlayer(), SIGNAL(metaDataAvailableChanged(bool)), this, SLOT(updateInfo()));
}

SongPlayer::~SongPlayer()
{
}

void SongPlayer::updateState()
{
    if (mediaPlayer_->position() >= mediaPlayer_->duration() && mediaPlayer_->duration() != -1)
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
    if (loop_)
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

    togglePlayback(true);
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
    if (shuffle_)
    {
        openShuffle();
    }
    else
    {
        openPrevious();
    }

    togglePlayback(true);
}

void SongPlayer::togglePlayback(bool play)
{
//    if (mediaPlayer_->mediaStatus() == MediaStatus::NoMedia)
//    {
//        if (shuffle_)
//        {
//            openShuffle();
//        }
//        else
//        {
//            openFile();
//        }

//        mediaPlayer_->play();
//    }
    if (play)
    {
        mediaPlayer_->play();
    }
    else
    {
        mediaPlayer_->pause();
    }
}

void SongPlayer::setFile(const QString& filePath)
{
    mediaPlayer_->setMedia(filePath);
}

void SongPlayer::durationChanged(qint64 duration)
{
    duration_ = duration;
}

void SongPlayer::positionChanged(qint64 position)
{
    position_ = position;
//    qDebug() << "position: " << position;
    emit updateProgress(position_, duration_);
}

void SongPlayer::adjustVolume(int volume)
{
    mediaPlayer_->setVolume(volume);
}

void SongPlayer::toggleShuffle()
{
    if (shuffle_)
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
    if (loop_)
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
    artist_ = mediaPlayer_->metaData(QMediaMetaData::ContributingArtist);
    title_ = mediaPlayer_->metaData(QMediaMetaData::Title);
    album_ = mediaPlayer_->metaData(QMediaMetaData::AlbumTitle);

    //remove all spaces in album name for easier access to file path of album
    album_.replace(" ", "");

    cover_ = (ALBUM_FILE_PATH);
    cover_.append(album_);

    QPixmap img(cover_);

    emit updateGUI(title_, artist_, img);
}

QColor SongPlayer::getColor(QImage img)
{
    int height = img.height() / 2;
    int width = img.width() / 2;

    //height and width are set to 0 when the song changes.
    if (height != 0 && width != 0)
    {
        QColor color(img.pixel(width, height));

        while (color.lightness() < MIN_LIGHT)
        {
            QColor temp(img.pixel(width += SKIP_PIXELS, height += SKIP_PIXELS));
            color = temp;

            if (width >= img.width() - SKIP_PIXELS || height >= img.height() - SKIP_PIXELS)
            {
                QColor white = QColor(255, 255, 255, 255);
                color = white;
            }
        }

        return color;
    }
}
