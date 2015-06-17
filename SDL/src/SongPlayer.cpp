#include "SongPlayer.h"
#include "SongLoader.h"

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
	enum threadMode { PLAY, NEXT, PREVIOUS, SHUFFLE };
	threadMode mode = PLAY;

void songQuit()
{
	quitSong = true;
}

void initSongPlayer()
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
int loadSong(char* songName)
{
	printf("loadSong: Trying to load %s\n",songName);

	if(loaded){
		printf("loadSong: calling freeMusic()\n");
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
   /* if (pathWithSong != NULL)
		delete[] pathWithSong;
	//pathWithSong = NULL;*/

	loaded = true;
	printf("loadSong: Loaded %s!\n",songName);
}
//don't need this anymore
int playSong()
{

}
//dont need this anymore
int pauseSong()
{
	printf("Called pauseSong\n");

}


int previousSong()
{
	mode = PREVIOUS;
}

int nextSong()
{
	mode = NEXT;
}


std::string currentSong()
{
	return loader.currentSong();
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
	-dev is re-created accorprependNameding to the song mh.  
*/
int songThread(void *data)
{
	usleep(1000);
    size_t done;

	while (!quitSong)
	{

		switch(mode){

		case PLAY:
			if (mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK){
        		ao_play(dev, (char*)buffer, done);
        	}
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



		}
	}
}
