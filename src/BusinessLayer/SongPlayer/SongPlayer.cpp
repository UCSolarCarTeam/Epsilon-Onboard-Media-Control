#include "SongPlayer.h"
#include <QDebug>

namespace
{
    const int MS_TO_MINUTES = 60000;
    const double MS_TO_SECONDS = 1000.0;
    const QString ALBUM_FILE_PATH = QDir::homePath() + "/Pictures/Covers/";
    const QColor BASELINE_COLOR = QColor(0, 0, 0, 255);
    const int IMAGE_PARTITIONS = 2;
    const int STEP = 2;
    const int SATURATION_OFFSET = 10;
}

SongPlayer::SongPlayer(QWidget* parent) : QWidget(parent)
    , controller_(new SongControl())
    , mediaPlayer_(new LibMpgMediaPlayer(controller_.data()))
    , shuffle_(false)
    , loop_(false)
{
    connect(mediaPlayer_.data(), SIGNAL(stateChanged()), this, SLOT(updateState()));
    connect(mediaPlayer_.data()->getSongPlayerThread(), SIGNAL(durationChanged(qint64)), this, SLOT(durationChanged(qint64)));
    connect(mediaPlayer_.data()->getSongPlayerThread(), SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    connect(mediaPlayer_.data()->getSongPlayerThread(), SIGNAL(metaDataAvailableChanged(bool)), this, SLOT(updateInfo()));
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

QColor SongPlayer::getColor(QImage img, int threadID)
{
    //Recieves an image from the view layer and the id of the thread this function is running in.
    //Uses the thread id to partition the image into smaller chunks. Each thread finds the brightest color
    //in its segment and returns it.
    int height = img.height();
    int width = img.width();
    int size = qMin(img.width(), img.height());
    int start_x = (size / IMAGE_PARTITIONS) * (threadID % IMAGE_PARTITIONS);
    int start_y  = (size / IMAGE_PARTITIONS) * (threadID / IMAGE_PARTITIONS);
    int x = (size / IMAGE_PARTITIONS) * ((threadID % IMAGE_PARTITIONS) + 1);
    int y = (size / IMAGE_PARTITIONS) * ((int)(threadID / IMAGE_PARTITIONS) + 1);

    QColor brightest = BASELINE_COLOR;

    //height and width are set to 0 when the song changes.
    if (height != 0 && width != 0)
    {
        brightest.setHsv(0, 0, 40, 255);
        QColor temp;

        for (int i = start_x; i < x; i += STEP)
        {
            for (int j = start_y; j < y; j += STEP)
            {
                temp = img.pixel(i, j);

                if (temp.value() > brightest.value() && temp.saturation() > brightest.saturation() - SATURATION_OFFSET)
                {
                    brightest = temp;
                }
            }
        }
    }

    return brightest;
}
