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
int SongPlayer::load(std::string songName)
{
	/* open the file and get the decoding format */
	mpg123_open(mh, argv[1]);
    mpg123_getformat(mh, &rate, &channels, &encoding);

    /* set the output format and open the output device */
    format.bits = mpg123_encsize(encoding) * BITS;
    format.rate = rate;
    format.channels = channels;
    format.byte_format = AO_FMT_NATIVE;
    format.matrix = 0;
    dev = ao_open_live(driver, &format, NULL);
}

int SongPlayer::play()
{
	playing = true;
}
int SongPlayer::back()
{
	pause();
	//load(loader.previousSong());
	play();
}
int SongPlayer::next()
{
	load(loader.nextSong());
}
int SongPlayer::pause()
{
	playing = false;
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
 		struct mpg123_frameinfo fInfo;


	} else {
		return 1;
	}

}

int SongPlayer::freeMusic()
{
	free(songBuffer);
    // ao_close(dev);
    // mpg123_close(mh);
    // mpg123_delete(mh);
    // mpg123_exit();
    // ao_shutdown();
}

SongPlayer::~SongPlayer()
{
	freeMusic();
}



int SongPlayer::songThread()
{
	/* these variables can be local to the function */
    unsigned char *buffer;
    size_t buffer_size;
    size_t done;
    int err;

    int driver;
    ao_device *dev;

    ao_sample_format format;
    int channels, encoding;
    long rate;

    driver = ao_default_driver_id();
    mh = mpg123_new(NULL, &err);
    buffer_size = mpg123_outblock(mh);
    buffer = (unsigned char*) malloc(buffer_size * sizeof(unsigned char));

	while (true)
	{
		if (playing)
		{
			if (mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK)
        		ao_play(dev, (char*)buffer, done);
		}
	}
}