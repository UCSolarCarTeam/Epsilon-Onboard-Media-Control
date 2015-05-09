#ifndef SONG_LOADER_H
#define SONG_LOADER_H
#include <string>
class SongLoader 
{
		public:
			SongLoader();
			int readSongNames(std::string container[]);
			const int MAX_SIZE = 20000;
	
};
#endif
