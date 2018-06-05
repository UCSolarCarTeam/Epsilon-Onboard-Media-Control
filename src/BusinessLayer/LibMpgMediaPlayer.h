#pragma once
#include <QMediaPlayer>
#include "SongPlayer/I_MediaPlayer.h"
#include <ao/ao.h>
#include <mpg123.h>

class LibMpgMediaPlayer : public I_MediaPlayer
{
    Q_OBJECT
public:
    LibMpgMediaPlayer();
    qint64 position();
    qint64 duration();
    MediaStatus mediaStatus();
    void setMedia(const QString& filePath);
    void setVolume(int volume);
    QString metaData(const QString& key);
    void play();
    void pause();
    PlayerState state();

signals:
    void stateChanged();
    void durationChanged(qint64);
    void positionChanged(qint64);
    void metaDataAvailableChanged(bool);

private:
    double volume;
    double MAX_VOLUME;
    void freeMusic();
    int loadSong(char* songName);

    /*mpg123 specific variables*/
    unsigned char* buffer;
    size_t buffer_size;
    bool loaded;
    mpg123_handle* mh;
    ao_sample_format format;
    ao_device* dev;
    int channels, encoding;
    long rate;
    bool quitSong;
};
