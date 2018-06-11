/**
 *  Schulich Delta OnBoard Media Control
 *  Copyright (C) 2015 University of Calgary Solar Car Team
 *
 *  This file is part of the Schulich Delta OnBoard Media Control
 *
 *  The Schulich Delta OnBoard Media Control is free software:
 *  you can redistribute it and/or modify it under the terms
 *  of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  The Schulich Delta OnBoard Media Control is distributed
 *  in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 *  without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Affero
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General
 *  Public License along with the Schulich Delta OnBoard Media
 *  Control.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  For further contact, email <software@calgarysolarcar.ca>
 */

#include "DeltaSongPlayer.h"
#include "LibMpgMediaPlayer.h"
#include <QDebug>
//#include "SongLoader.h"

namespace
{
    const double SECONDS_TO_MS = 1000.0;
}

DeltaSongPlayer::DeltaSongPlayer(SongControl* songControl)
    : songControl_(songControl)
{
    MAX_VOLUME = 1.0;

    loaded = false;
    quitSong = false;
    dev = NULL;
    mh = NULL;
    buffer = NULL;

    ao_initialize();

    mpg123_init();
    mode = PAUSE;
    volume = MAX_VOLUME;
}
DeltaSongPlayer::~DeltaSongPlayer()
{
    closeDeltaSongPlayer();
}
void DeltaSongPlayer::songQuit()
{
    quitSong = true;
}

void DeltaSongPlayer::changeVolume(double change)
{
    volume = change;
    if (volume > MAX_VOLUME)
    {
        volume = MAX_VOLUME;
    } else if (volume < 0) {
        volume = 0;
    }

    mpg123_volume(mh, volume);
}

double DeltaSongPlayer::getVolume()
{
    return volume;
}

double DeltaSongPlayer::getMaxVolume()
{
    return MAX_VOLUME;
}

//Will load the songName into buffer
int DeltaSongPlayer::loadSong(QString filePath)
{
    mode = PAUSE;
    QByteArray ba = filePath.toLocal8Bit();
    int size = ba.length();
    char* songName = new char[size];
    songName = ba.data();

    if (NULL == songName || 0 == strcmp("", songName))
    {
        return -1;
    }

    if(loaded){
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
    format.bits = mpg123_encsize(encoding) * BITS;
    format.rate = rate;
    format.channels = channels;
    format.byte_format = AO_FMT_NATIVE;
    format.matrix = 0;

    // most important thing used in thread later
    dev = ao_open_live(driver, &format, NULL);

    // loading song metadata
    mpg123_id3(mh, NULL, &metaData);

    loaded = true;
    mode = PLAY;

    emit durationChanged(getSongLength() * SECONDS_TO_MS);
    emit metaDataAvailableChanged(true);
    return 0;
}

void DeltaSongPlayer::play()
{
    if(mode == PAUSE)
    {
        mode = PLAY;
    }
}

void DeltaSongPlayer::pause()
{
    if(mode != PAUSE)
    {
        mode = PAUSE;
    }
}

QString DeltaSongPlayer::currentSongAlbum()
{
    QString album = metaData->album->p;
    return album;
}

QString DeltaSongPlayer::currentSongArtist()
{
    QString artist = metaData->artist->p;
    return artist;
}

QString DeltaSongPlayer::currentSongTitle()
{
   QString title = metaData->title->p;
   return title;
}


double DeltaSongPlayer::getCurrentTime()
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
        return timem*60 + times;

    }
    else
    {
        return 1;
    }
}
double DeltaSongPlayer::getSongLength()
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
        return timem*60+times;
    }
    else
    {
        return -1;
    }
}

void DeltaSongPlayer::freeMusic()
{
    free(buffer);
    ao_close(dev);
    mpg123_close(mh);
    mpg123_delete(mh);
}

void DeltaSongPlayer::closeDeltaSongPlayer()
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
void DeltaSongPlayer::ThreadFunction()
{
    size_t done;

    while (!quitSong)
    {
        switch(mode){

        case PLAY:
            if (mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK)
                ao_play(dev, (char*)buffer, done);

            if (getCurrentTime() >= getSongLength())
                mode = NEXT;
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
