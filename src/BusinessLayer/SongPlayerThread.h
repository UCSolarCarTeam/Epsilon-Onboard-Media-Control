# pragma once

#include <ao/ao.h>
#include <mpg123.h>
#include <unistd.h>
#include "ThreadClass.h"
#include "SongControl/SongControl.h"

#define BITS 8

class SongPlayerThread : public I_ThreadClass
{
    Q_OBJECT
public:
    SongPlayerThread(SongControl* songControl);
    ~SongPlayerThread();

    void closeSongPlayerThread();

    /*Song Control*/
    void play();
    void pause();
    void changeVolume(double change);

    /*For the time bar*/
    double getCurrentTime();
    double getSongLength();
    double getVolume();
    double getMaxVolume();
    QString currentSongAlbum();
    QString currentSongArtist();
    QString currentSongTitle();

    void songQuit();
    int loadSong(QString filePath);
    int loadMetaData(QString filePath);
signals:
    void durationChanged(qint64);
    void positionChanged(qint64);
    void metaDataAvailableChanged(bool);

protected:
    void ThreadFunction();

private:
    double MAX_VOLUME;

    void freeMusic();
    SongControl* songControl_;
    double volume_;

    /*mpg123 specific variables*/
    unsigned char* buffer_;
    size_t bufferSize_;
    bool loaded_;
    mpg123_handle* mh_;
    ao_sample_format format_;
    ao_device* dev_;
    int channels_;
    int encoding_;
    long rate_;
    bool quitSong_;
    char* mcurrentSong_;
    mpg123_id3v2* metaData_;

    /*Modes*/
    enum threadMode { PLAY, NEXT, PREVIOUS, SHUFFLE, PAUSE};
    threadMode mode_;
};
