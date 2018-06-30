#pragma once

#include <QMediaPlayer>
#include "SongControl/SongControl.h"
#include "SongPlayer/I_MediaPlayer.h"
#include "SongPlayerThread.h"

class LibMpgMediaPlayerThread;
class SongPlayerThread;

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

    SongPlayerThread* getSongPlayerThread();

signals:
    void stateChanged();

private:
    SongPlayerThread* songPlayer_;
    SongControl* songControl_;
    double volume_;
    double MAX_VOLUME;
    int loadSong(char* songName);

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
    MediaStatus status_;
    PlayerState state_;

    /*Modes*/
    enum threadMode { PLAY, NEXT, PREVIOUS, SHUFFLE, PAUSE};
    threadMode mode_;
};
