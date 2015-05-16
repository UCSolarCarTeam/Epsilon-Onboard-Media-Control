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
	unsigned char *songBuffer;
	bool playing;
	SongLoader loader;

	/*For the time bar*/


	int load(std::string songName);
	int freeMusic();

	/*Functions to change 'bool playing' to true or false*/
	void start();
	void stop();

	int songThread();
};

#endif /* SONGPLAYER_H */

