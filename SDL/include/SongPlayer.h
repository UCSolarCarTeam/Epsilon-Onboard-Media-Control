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


/*************Public Functions*************/	
	void initSongPlayer();
	void closeSongPlayer();

	/*Song Control*/
	int previousSong();
	int nextSong(); 
	int playPause();
	void changeVolume(double change);

	/*For the time bar*/
	int getCurrentTime();
	int getSongLength();
	std::string currentSong();
	
/*************Private Functions*************/	
	int freeMusic();
	int loadSong(char* songName);

	/*The Thread*/
	int songThread(void *data);
	void songQuit();
	
//};



#endif /* SONGPLAYER_H */

