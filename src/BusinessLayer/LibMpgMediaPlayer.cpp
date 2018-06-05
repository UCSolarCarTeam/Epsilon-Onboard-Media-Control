#include "LibMpgMediaPlayer.h"
#include <ao/ao.h>
#include <mpg123.h>
#include <string>
#include <cstring>
#include <unistd.h>
#include <QDebug>


LibMpgMediaPlayer::LibMpgMediaPlayer()
{
    MAX_VOLUME = 0.4;
    loaded = false;
    quitSong = false;
    dev = NULL;
    mh = NULL;
    buffer = NULL;
    ao_initialize();
    mpg123_init();
    //mode = PLAY;
    volume = MAX_VOLUME / 3;
}
void LibMpgMediaPlayer::play()
{

}
void LibMpgMediaPlayer::pause()
{

}
qint64 LibMpgMediaPlayer::position()
{
    return 0;
}
qint64 LibMpgMediaPlayer::duration()
{
    return 0;
}
MediaStatus LibMpgMediaPlayer::mediaStatus()
{
    MediaStatus status = MediaStatus::Error;
    return status;
}

PlayerState LibMpgMediaPlayer::state()
{
    PlayerState status = PlayerState::Stopped;
    return status;
}

void LibMpgMediaPlayer::setMedia(const QString& filePath)
{
    QByteArray ba = filePath.toLocal8Bit();
    int size = ba.length();
    char* songName = new char[size];
    songName = ba.data();
    qDebug() << "Trying to load " << songName;

    if (NULL == songName || 0 == strcmp("", songName))
    {
        return;
    }

    if (loaded)
    {
        qDebug() << "calling freeMusic()\n";
        freeMusic();
    }

    int driver;
    int err;
    driver = ao_default_driver_id();
    mh = mpg123_new(NULL, &err);
    mpg123_volume(mh, volume);
    // open the file and get the decoding format
    mpg123_open(mh, songName);
    mpg123_getformat(mh, &rate, &channels, &encoding); // error: Invalid UTF16 surrogate pair at 10 (0xff08). when running this line
    buffer_size = mpg123_outblock(mh);
    buffer = (unsigned char*) malloc(buffer_size * sizeof(unsigned char));

    // set the output format and open the output device
    #define BITS 8
    format.bits = mpg123_encsize(encoding) * BITS;
    format.rate = rate;
    format.channels = channels;
    format.byte_format = AO_FMT_NATIVE;
    format.matrix = 0;

    // most important thing used in thread later
    dev = ao_open_live(driver, &format, NULL);

    loaded = true;
    qDebug() << "Loaded " << songName;
}
void LibMpgMediaPlayer::setVolume(int volume)
{
    this->volume = static_cast<double>(volume) / 100.0;
}
QString LibMpgMediaPlayer::metaData(const QString& key)
{
    Q_UNUSED(key);
    return "Ben is Fat";
}

void LibMpgMediaPlayer::freeMusic()
{
    free(buffer);
    ao_close(dev);
    mpg123_close(mh);
    mpg123_delete(mh);
}
