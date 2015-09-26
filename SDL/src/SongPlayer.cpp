#include "SongPlayer.h"
#include "SongLoader.h"


void SongPlayer::songQuit()
{
    quitSong = true;
}

int SongPlayer::initSongPlayer()
{
    return loader.libraryLoad();
}

void SongPlayer::changeVolume(double change)
{
    double baseVolume, realVolume, decibels;
    mpg123_getvolume(mh, &baseVolume, &realVolume, &decibels);
    if ( baseVolume < 2.0 || change < 0)
        mpg123_volume_change(mh, change);
}

/** Max Volume is 2.0 **/
double SongPlayer::getVolume()
{
    double baseVolume, realVolume, decibels;
    mpg123_getvolume(mh, &baseVolume, &realVolume, &decibels);
    return baseVolume;
}

SongPlayer::SongPlayer()
{
    SongLoader loader();

    loaded = false;
    quitSong = false;
    dev = NULL;
    mh = NULL;
    buffer = NULL;

    ao_initialize();

    mpg123_init();
}

//Will load the songName into buffer
int SongPlayer::loadSong(char* songName)
{
    printf("loadSong: Trying to load %s\n",songName);
    if (NULL == songName || 0 == strcmp("", songName))
    {
        return -1;
    }

    if(loaded){
        printf("loadSong: calling freeMusic()\n");
        freeMusic();
    }

    int driver;
    int err;
    driver = ao_default_driver_id();
    mh = mpg123_new(NULL, &err);
    // open the file and get the decoding format
    mpg123_open(mh, songName);
    mpg123_getformat(mh, &rate, &channels, &encoding); // error: Invalid UTF16 surrogate pair at 10 (0xff08). when running this line
    buffer_size = mpg123_outblock(mh);
    buffer = (unsigned char*) malloc(buffer_size * sizeof(unsigned char));

    // set the output format and open the output device
    format.bits = mpg123_encsize(encoding) * BITS;
    format.rate = rate;
    format.channels = channels;
    format.byte_format = AO_FMT_NATIVE;
    format.matrix = 0;

    // most important thing used in thread later
    dev = ao_open_live(driver, &format, NULL);

    loaded = true;
    printf("loadSong: Loaded %s!\n",songName);
    return 0;
}
int SongPlayer::previousSong()
{
    mode = PREVIOUS;
}

int SongPlayer::nextSong()
{
    mode = NEXT;
}

int SongPlayer::playPause()
{
    if(mode == PAUSE)
    {
        mode = PLAY;
    }
    else
    {
        mode = PAUSE;
    }
}


std::string SongPlayer::currentSong()
{
    return loader.currentSong();
}


double SongPlayer::getCurrentTime()
{
    if(loaded)
    {
        off_t length;
        double times;
        int timem;
        length = mpg123_tell(mh);
        times = (double)(length/rate)/60;
        timem = times;
        times = (times - (double)timem) * 60;
        return timem + times/100;

    }
    else
    {
        return 1;
    }
}
double SongPlayer::getSongLength()
{
    if(loaded)
    {
        off_t length;
        double times;
        int timem;
        length = mpg123_length(mh);
        times = (double)(length/rate)/60; //time in minutes.minutes (e.g 5.3 minutes)
        timem = times;                          //time in minutes (5)
        times = (times - (double)timem) * 60; //time in seconds (.3*60)
        return timem+times/100;
    }
    else
    {
        return -1;
    }
}

int SongPlayer::freeMusic()
{
    free(buffer);
    ao_close(dev);
    mpg123_close(mh);
    mpg123_delete(mh);
}

void SongPlayer::closeSongPlayer()
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
void SongPlayer::InternalThreadEntry()
{
    usleep(1000);
    size_t done;

    while (!quitSong)
    {

        switch(mode){

        case PLAY:
            if (mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK)
                ao_play(dev, (char*)buffer, done);

            // stuff for testing
            double time, sec;
            int min;
            time = getCurrentTime();
            min = (int)time;
            time -= min;
            sec = (time*100);
            //printf("%d:%02.0lf\n", min, sec);
            //

            if (getCurrentTime() >= getSongLength())
                mode = NEXT;
            break;

        case NEXT:
            loadSong((char*)loader.nextSong().c_str());
            mode = PLAY;
            break;

        case PREVIOUS:
            loadSong((char*)loader.previousSong().c_str());
            mode = PLAY;
            break;

        case SHUFFLE:

            break;

        case PAUSE:
            //Keeps the thread looping every 0.2 seconds (So we don't kill CPU cycles on this thread)
            usleep(200000);
            break;


        }
    }
}
