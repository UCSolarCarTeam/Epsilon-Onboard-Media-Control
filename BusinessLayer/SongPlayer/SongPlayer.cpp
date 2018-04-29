#include "SongPlayer.h"

namespace
{
    const int MS_TO_MINUTES = 60000;
    const double MS_TO_SECONDS = 1000.0;
    const int MIN_LIGHT = 40;
    const int SKIP_PIXELS = 10;
    const int PAGE_STEP_INCREMENTS = 10;
    const QString SONG_FILE_PATH = "SongLibrary/";
    const QString ALBUM_FILE_PATH = "Covers/";
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
    else if(shuffle_)
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
<<<<<<< HEAD

    //retrieves the album name from current song
=======
>>>>>>> master
    album_ = mediaPlayer_.metaData(QMediaMetaData::AlbumTitle).toString();

    //remove all spaces in album name for easier access to file path of album
    album_.replace(" ", "");
<<<<<<< HEAD
=======

>>>>>>> master
    cover_ = controller_->currentSong();

    int songNameLength = cover_.length() - cover_.lastIndexOf(SONG_FILE_PATH) + SONG_FILE_PATH.length();

    //manipulate the current song filepath string to the album file path
    cover_.replace(cover_.lastIndexOf(SONG_FILE_PATH), SONG_FILE_PATH.length(), ALBUM_FILE_PATH);
    cover_.replace(cover_.lastIndexOf(ALBUM_FILE_PATH) + ALBUM_FILE_PATH.length(), songNameLength, album_);

    QPixmap img(cover_);

    emit updateGUI(title_, artist_, img);
}

QColor SongPlayer::getColor(QImage img)
{
    int height = img.height() / 2;
    int width = img.width() / 2;

    //height and width are set to 0 when the song changes.
    if(height != 0 && width != 0)
    {
        QColor color(img.pixel(width, height));
        while(color.lightness() < MIN_LIGHT)
        {
            QColor temp(img.pixel(width += SKIP_PIXELS, height += SKIP_PIXELS));
            color = temp;
            if(width >= img.width() - SKIP_PIXELS || height >= img.height() - SKIP_PIXELS)
            {
                QColor white = QColor(255,255,255,255);
                color = white;
            }
        }
        return color;
    }
}
