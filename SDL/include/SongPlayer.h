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

class SongPlayer : public MyThreadClass
{
    std::string message;
    
    public:
        SongPlayer();

        int initSongPlayer();
        void closeSongPlayer();

        /*Song Control*/
        int previousSong();
        int nextSong();
        int playPause();
        void changeVolume(double change);

        /*For the time bar*/
        double getCurrentTime();
        double getSongLength();
        double getVolume();
        std::string currentSong();

        void songQuit();
    protected:
        void InternalThreadEntry();

    private: 
        int freeMusic();
        int loadSong(char* songName);

        /*The Thread*/
        //int songThread(void *data);
        
        unsigned char *buffer;
        size_t buffer_size;
        bool loaded;
        SongLoader loader;
        mpg123_handle *mh;
        ao_sample_format format;
        ao_device *dev;
        int channels, encoding;
        long rate;
        bool quitSong;
        //The Modes the songThread can be in.
        enum threadMode { PLAY, NEXT, PREVIOUS, SHUFFLE, PAUSE};
        threadMode mode = PLAY;
};

#endif /* SONGPLAYER_H */

