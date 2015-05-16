#ifndef SONG_LOADER_H
#define SONG_LOADER_H
#include <string>
#include <stdlib.h>
#include <iostream>
#include <dirent.h>

//Headers for Randomizing
#include <algorithm>
#include <vector>
#include <random>



class SongLoader 
{
	int counter,song;
	std::string container[100];
	std::string CurrentSong;
	std::string PastSongs[10];

	
		public:
			SongLoader();
			int readSongNames(); //Read all the songs in the directory
			int shuffleSongNames(); //Shuffle all the songs in the directory
			int sortSongNames();
			int rearrangeArray();
			std::string nextSong(); //Returns Next song
			
			

	
};
#endif
