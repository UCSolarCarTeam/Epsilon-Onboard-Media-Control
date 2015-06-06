#include "SongPlayer.h"
#include "SongLoader.h"

unsigned char *buffer;
size_t buffer_size;
bool playing;
bool loaded;
SongLoader loader;
mpg123_handle *mh;
ao_sample_format format;
ao_device *dev;
int channels, encoding;
long rate;
bool quitSong;

void songQuit()
{
	quitSong = true;
}

void initSongPlayer()
{
	SongLoader loader(); 
	playing = false;
	loaded = false;
	quitSong = false;
	dev = NULL;
	mh = NULL;
	buffer = NULL;

    ao_initialize();

	mpg123_init();
}

//Will load the songName into buffer
int loadSong(char* songName)
{
	if(loaded){
		freeMusic();
	}

    //unsigned char *buffer;
    //size_t buffer_size;

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
}

int playSong()
{
	playing = true;
}
int pauseSong()
{
	playing = false; 
}
int previousSong()
{
	pauseSong();
	loadSong((char*)loader.previousSong()); 
	playSong();
}
int nextSong()
{
	pauseSong();
	loadSong((char*)loader.nextSong());
	playSong();
}

int getCurrentTime()
{
	if(loaded){




	} else {
		return 1;
	}
}
int getSongLength()
{
	if(loaded){
 		off_t length;
 		double times;
 		int timem;
 		mpg123_scan(mh);
 		length = mpg123_length(mh);
		times = (double)(length/rate)/60; //time in minutes.minutes (e.g 5.3 minutes)
		timem = times;         				 	//time in minutes (5)
		times = (times - (double)timem) * 60; //time in seconds (.3*60)
		return timem+times/10; 
	} else {
		return -1;
	}
}

int freeMusic()
{
	free(buffer);
    ao_close(dev);
    mpg123_close(mh);
    mpg123_delete(mh);
}

void closeSongPlayer()
{
	freeMusic();
	ao_shutdown();
	mpg123_exit();
}



/* Variables that are changed external to this thread
	-mh, the song that is loaded
	-buffer, the buffer is re-created depending on the frame size of mh
	-buffer_size is also changed according to frame size
	-dev is re-created according to the song mh.  
	-playing is going to be changed by pause() and play().

*/
int songThread(void *data)
{
    size_t done;

	while (!quitSong)
	{
		if (playing)
		{
			if (mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK)
        		ao_play(dev, (char*)buffer, done);
		}
	}
}
