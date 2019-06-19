#include "SongPlayerThread.h"
#include "LibMpgMediaPlayer.h"

namespace
{
    const double SECONDS_TO_MS = 1000.0;
}

SongPlayerThread::SongPlayerThread(SongControl* songControl)
    : songControl_(songControl)
{
    MAX_VOLUME = 1.0;

    loaded_ = false;
    quitSong_ = false;
    dev_ = NULL;
    mh_ = NULL;
    buffer_ = NULL;
    metaData_ = nullptr;
    ao_initialize();

    mpg123_init();
    mode_ = PAUSE;
    volume_ = MAX_VOLUME;
}
SongPlayerThread::~SongPlayerThread()
{
    closeSongPlayerThread();
}
void SongPlayerThread::songQuit()
{
    quitSong_ = true;
}

void SongPlayerThread::changeVolume(double change)
{
    volume_ = change;

    if (volume_ > MAX_VOLUME)
    {
        volume_ = MAX_VOLUME;
    }
    else if (volume_ < 0)
    {
        volume_ = 0;
    }

    mpg123_volume(mh_, volume_);
}

double SongPlayerThread::getVolume()
{
    return volume_;
}

double SongPlayerThread::getMaxVolume()
{
    return MAX_VOLUME;
}

int SongPlayerThread::loadMetaData(QString filePath)
{
    QByteArray ba = filePath.toLocal8Bit();
    int size = ba.length();
    char* songName = new char[size];
    songName = ba.data();

    if (NULL == songName || 0 == strcmp("", songName))
    {
        return -1;
    }

    if (loaded_)
    {
        freeMusic();
    }

    int err;
    mh_ = mpg123_new(NULL, &err);
    mpg123_open(mh_, songName);
    mpg123_getformat(mh_, &rate_, &channels_, &encoding_);
    mpg123_id3(mh_, NULL, &metaData_);

    //emit metaDataAvailableChanged(true);
    return 0;
}

//Will load the songName into buffer
int SongPlayerThread::loadSong(QString filePath)
{
    mode_ = PAUSE;
    QByteArray ba = filePath.toLocal8Bit();
    int size = ba.length();
    char* songName = new char[size];
    songName = ba.data();

    if (NULL == songName || 0 == strcmp("", songName))
    {
        return -1;
    }

    if (loaded_)
    {
        freeMusic();
    }

    int driver;
    int err;
    driver = ao_default_driver_id();
    mh_ = mpg123_new(NULL, &err);
    mpg123_volume(mh_, volume_);
    // open the file and get the decoding format
    mpg123_open(mh_, songName);
    mpg123_getformat(mh_, &rate_, &channels_, &encoding_); // error: Invalid UTF16 surrogate pair at 10 (0xff08). when running this line
    bufferSize_ = mpg123_outblock(mh_);
    buffer_ = (unsigned char*) malloc(bufferSize_ * sizeof(unsigned char));

    // set the output format and open the output device
    format_.bits = mpg123_encsize(encoding_) * BITS;
    format_.rate = rate_;
    format_.channels = channels_;
    format_.byte_format = AO_FMT_NATIVE;
    format_.matrix = 0;

    // opens a live  audio device for output
    dev_ = ao_open_live(driver, &format_, NULL);

    // loading song metadata
    mpg123_id3(mh_, NULL, &metaData_);

    loaded_ = true;
    mode_ = PLAY;

    emit durationChanged(getSongLength() * SECONDS_TO_MS);
    emit metaDataAvailableChanged(true);
    return 0;
}



void SongPlayerThread::play()
{
    if (mode_ == PAUSE)
    {
        mode_ = PLAY;
    }
}

void SongPlayerThread::pause()
{
    if (mode_ != PAUSE)
    {
        mode_ = PAUSE;
    }
}

QString SongPlayerThread::currentSongAlbum()
{
    QString album = metaData_->album->p;
    return album;
}

QString SongPlayerThread::currentSongArtist()
{
    QString artist = metaData_->artist->p;
    return artist;
}

QString SongPlayerThread::currentSongTitle()
{
    QString title = metaData_->title->p;
    return title;
}


double SongPlayerThread::getCurrentTime()
{
    if (loaded_)
    {
        off_t length;
        double timeSecs;
        int timeMins;
        length = mpg123_tell(mh_);
        timeSecs = (double)(length / rate_) / 60;
        timeMins = timeSecs;
        timeSecs = (timeSecs - (double)timeMins) * 60;
        return timeMins * 60 + timeSecs;

    }
    else
    {
        return 1;
    }
}
double SongPlayerThread::getSongLength()
{
    if (loaded_)
    {
        off_t length;
        double timeSecs;
        int timeMins;
        length = mpg123_length(mh_);
        timeSecs = (double)(length / rate_) / 60; //time in minutes.minutes (e.g 5.3 minutes)
        timeMins = timeSecs;                         //time in minutes (5)
        timeSecs = (timeSecs - (double)timeMins) * 60;  //time in seconds (.3*60)
        return timeMins * 60 + timeSecs;
    }
    else
    {
        return -1;
    }
}

void SongPlayerThread::freeMusic()
{
    free(buffer_);
    ao_close(dev_);
    mpg123_close(mh_);
    mpg123_delete(mh_);
}

void SongPlayerThread::closeSongPlayerThread()
{
    freeMusic();
    ao_shutdown();
    mpg123_exit();
}

/* Variables that are changed external to this thread
    -mh, the song that is loaded
    -buffer, the buffer is re-created depending on the frame size of mh
    -buffer_size is also changed according to frame size
    -dev is re-created accorprependNameding to the song mh.
*/
void SongPlayerThread::ThreadFunction()
{
    size_t done;

    while (!quitSong_)
    {
        switch (mode_)
        {

            case PLAY:
                if (mpg123_read(mh_, buffer_, bufferSize_, &done) == MPG123_OK)
                {
                    ao_play(dev_, (char*)buffer_, done);
                }

                if (getCurrentTime() >= getSongLength())
                {
                    mode_ = NEXT;
                }

                break;

            case NEXT:
                loadSong(songControl_->nextSong());
                break;

            case PREVIOUS:
                loadSong(songControl_->previousSong());
                break;

            case SHUFFLE:
                break;

            case PAUSE:
                //Keeps the thread looping every 0.2 seconds (So we don't kill CPU cycles on this thread)
                usleep(200000);
                break;
        }

        emit positionChanged(getCurrentTime() * SECONDS_TO_MS);
    }
}
