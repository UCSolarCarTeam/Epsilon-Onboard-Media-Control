#pragma once
#include <QMediaPlayer>
#include <QThread>
#include "SongPlayer/I_MediaPlayer.h"
#include "SongControl/SongControl.h"
#include <ao/ao.h>
#include <mpg123.h>
#include "DeltaSongPlayer.h"

class LibMpgMediaPlayerThread;
class DeltaSongPlayer;

class LibMpgMediaPlayer : public I_MediaPlayer
{
    Q_OBJECT
public:
    LibMpgMediaPlayer(SongControl* songControl);
    qint64 position();
    qint64 duration();
    MediaStatus mediaStatus();
    void setMedia(const QString& filePath);
    void setVolume(int volume);
    QString metaData(const QString& key);
    void play();
    void pause();
    PlayerState state();

    DeltaSongPlayer* getDeltaSongPlayer();

signals:
    void stateChanged();
    void metaDataAvailableChanged(bool);

private:
    DeltaSongPlayer* songplayer;
    SongControl* songControl_;
    double volume;
    double MAX_VOLUME;
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
    MediaStatus status_;
    PlayerState state_;

    /*Modes*/
    enum threadMode { PLAY, NEXT, PREVIOUS, SHUFFLE, PAUSE};
    threadMode mode;
};
