#ifndef SONGPLAYER_H
#define SONGPLAYER_H
#include <ao/ao.h>
#include <mpg123.h>
#include <string>
#include "SongLoader.h"

#define BITS 8

class SongPlayer{

/*****************************************************************************
Public Functions
*/
	public:
	SongPlayer();

	int play();
	int back();
	int next(); 
	int pause();

	int getCurrentTime();
	int getSongLength();

	~SongPlayer();


/*****************************************************************************
Private Functions
*/
	private:
	/*For the time bar*/
	int load(char* songName);
	int freeMusic();

	/*Functions to change 'bool playing' to true or false*/
	void start();
	void stop();

	/*The Thread*/
	int songThread();


	bool playing;
	bool loaded;
	SongLoader loader;

	mpg123_handle *mh;
	ao_sample_format format;
	ao_device *dev;
    int channels, encoding;
    long rate;
};



#endif /* SONGPLAYER_H */

