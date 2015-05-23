#include "SongPlayer.h"
#include "SongLoader.h"


SongPlayer::SongPlayer()
{
	SongLoader loader(); 
	playing = false;
	loaded = false;

    ao_initialize();

	mpg123_init();


}

//Will load the songName into buffer
int SongPlayer::load(char* songName)
{
	if(loaded){
		freeMusic();
	}

    unsigned char *buffer;
    size_t buffer_size;

	int driver;
	int err;

    mh = mpg123_new(NULL, &err);

	/* open the file and get the decoding format */
	mpg123_open(mh, songName);
    mpg123_getformat(mh, &rate, &channels, &encoding);

    buffer_size = mpg123_outblock(mh);
    buffer = (unsigned char*) malloc(buffer_size * sizeof(unsigned char));

    /* set the output format and open the output device */
    format.bits = mpg123_encsize(encoding) * BITS;
    format.rate = rate;
    format.channels = channels;
    format.byte_format = AO_FMT_NATIVE;
    format.matrix = 0;

    /*most important thing used in thread later*/
    dev = ao_open_live(driver, &format, NULL);
}

int SongPlayer::play()
{
	playing = true;
}
int SongPlayer::pause()
{
	playing = false; 
}
int SongPlayer::back()
{
	pause();
	load((char*)loader.previousSong()); 
	play();
}
int SongPlayer::next()
{
	pause();
	load((char*)loader.nextSong());
	play();
}

int SongPlayer::getCurrentTime()
{
	if(loaded){




	} else {
		return 1;
	}
}
int SongPlayer::getSongLength()
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

int SongPlayer::freeMusic()
{
	free(buffer);
    ao_close(dev);
    mpg123_close(mh);
    mpg123_delete(mh);
}

SongPlayer::~SongPlayer()
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
int SongPlayer::songThread()
{
    size_t done;

	while (true)
	{
		if (playing)
		{
			if (mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK)
        		ao_play(dev, (char*)buffer, done);
		}
	}
}