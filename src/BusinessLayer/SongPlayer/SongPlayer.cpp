#include "SongPlayer.h"
//#include "LibMpgMediaPlayer.h"

namespace
{
    const int MS_TO_MINUTES = 60000;
    const double MS_TO_SECONDS = 1000.0;
    const QString SONG_FILE_PATH = "SongLibrary/";
    const QString ALBUM_FILE_PATH = "Covers/";
    const QColor BASELINE_COLOR = QColor(0, 0, 0, 255);
    const int IMAGE_PARTITIONS = 2;
    const int STEP = 2;
    const int SATURATION_OFFSET = 10;
}

SongPlayer::SongPlayer(QWidget* parent) : QWidget(parent)
    , controller_(new SongControl())
    , shuffle_(false)
    , loop_(false)
    , mediaPlayer_(new LibMpgMediaPlayer(controller_.data()))
{
    connect(mediaPlayer_.data(), SIGNAL(stateChanged()), this, SLOT(updateState()));
    connect(mediaPlayer_.data(), SIGNAL(durationChanged(qint64)), this, SLOT(durationChanged(qint64)));
    connect(mediaPlayer_.data(), SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    connect(mediaPlayer_.data(), SIGNAL(metaDataAvailableChanged(bool)), this, SLOT(updateInfo()));
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
    if(play)
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

    cover_ = controller_->currentSong();

    int songNameLength = cover_.length() - cover_.lastIndexOf(SONG_FILE_PATH) + SONG_FILE_PATH.length();
    cover_.replace(cover_.lastIndexOf(SONG_FILE_PATH), SONG_FILE_PATH.length(), ALBUM_FILE_PATH);
    cover_.replace(cover_.lastIndexOf(ALBUM_FILE_PATH) + ALBUM_FILE_PATH.length(), songNameLength, album_);

    QPixmap img(cover_);

    emit updateGUI(title_, artist_, img);
}

QColor SongPlayer::getColor(QImage img, int thread_ID)
{
    //Recieves an image from the view layer and the id of the thread this function is running in.
    //Uses the thread id to partition the image into smaller chunks. Each thread finds the brightest color
    //in its segment and returns it.
    int height = img.height();
    int width = img.width();
    int size = qMin(img.width(), img.height());
//    int start_x = (size / IMAGE_PARTITIONS) * (thread_ID % IMAGE_PARTITIONS);
//    int start_y  = (size / IMAGE_PARTITIONS) * (thread_ID / IMAGE_PARTITIONS);
    int x = (size / IMAGE_PARTITIONS) * ((thread_ID % IMAGE_PARTITIONS) + 1);
    int y = (size / IMAGE_PARTITIONS) * ((int)(thread_ID / IMAGE_PARTITIONS) + 1);
    //height and width are set to 0 when the song changes.
//    if (height != 0 && width != 0)
//    {
//        QColor color(img.pixel(width, height));

//        while (color.lightness() < MIN_LIGHT)
//        {
//            QColor temp(img.pixel(width += SKIP_PIXELS, height += SKIP_PIXELS));
//            color = temp;

//            if (width >= img.width() - SKIP_PIXELS || height >= img.height() - SKIP_PIXELS)
//            {
//                QColor white = QColor(255, 255, 255, 255);
//                color = white;
//            }
//        }
    QColor color = BASELINE_COLOR;
    return color;
//        QColor brightest = BASELINE_COLOR;
//        brightest.setHsv(0,0,40,255);
//        QColor temp;
//        for(int i = start_x; i < x; i+=STEP)
//        {
//            for(int j = start_y; j < y; j+=STEP)
//            {
//                temp = img.pixel(i, j);
//                if(temp.value() > brightest.value() && temp.saturation() > brightest.saturation() - SATURATION_OFFSET)
//                {
//                    brightest = temp;
//                }
//            }
//        }
//        return brightest;
//    }

}
