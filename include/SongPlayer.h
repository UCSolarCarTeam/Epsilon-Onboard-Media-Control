#ifndef SONGPLAYER_H
#define SONGPLAYER_H

#include <ao/ao.h>
#include <mpg123.h>
#include <string>
#include "SongLoader.h"
#include <cstring>
#include <unistd.h>
#include "threadClass.hpp"

#define BITS 8

class SongPlayer : public I_ThreadClass
{
    public:
        SongPlayer();

        int initSongPlayer();
        void closeSongPlayer();

        /*Song Control*/
        void previousSong();
        void nextSong();
        void playPause();
        void changeVolume(double change);

        /*For the time bar*/
        double getCurrentTime();
        double getSongLength();
        double getVolume();
        double getMaxVolume();
        std::string currentSong();

        void songQuit();
    protected:
        void ThreadFunction();

    private: 
        double MAX_VOLUME;

        void freeMusic();
        int loadSong(char* songName);
        SongLoader loader;
        double volume;

        /*mpg123 specific variables*/ 
        unsigned char *buffer;
        size_t buffer_size;
        bool loaded;
        mpg123_handle *mh;
        ao_sample_format format;
        ao_device *dev;
        int channels, encoding;
        long rate;
        bool quitSong;

        /*Modes*/
        enum threadMode { PLAY, NEXT, PREVIOUS, SHUFFLE, PAUSE};
        threadMode mode;
};

#endif /* SONGPLAYER_H */

