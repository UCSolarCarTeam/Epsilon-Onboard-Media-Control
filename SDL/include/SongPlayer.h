#ifndef SONGPLAYER_H
#define SONGPLAYER_H

#include <ao/ao.h>
#include <mpg123.h>
#include <string>
#include "SongLoader.h"
#include <cstring>
#include <unistd.h>

#define BITS 8

//class SongPlayer{


	void initSongPlayer();

	int playSong();
	int previousSong();
	int nextSong(); 
	int pauseSong();

	int getCurrentTime();
	int getSongLength();
	
	/*For the time bar*/
	int loadSong(char* songName);
	int freeMusic();

	/*Functions to change 'bool playing' to true or false*/
	void startSong();
	void stopSong();

	/*The Thread*/
	int songThread(void *data);
	void songQuit();
	
	void closeSongPlayer();

	std::string currentSong();




//};



#endif /* SONGPLAYER_H */

