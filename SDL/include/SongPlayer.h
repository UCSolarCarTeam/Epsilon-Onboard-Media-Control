#ifndef SONGPLAYER_H
#define SONGPLAYER_H
#include <ao/ao.h>
#include <mpg123.h>
#include <string>

class SongPlayer{

	public:
	SongPlayer();
	int load(std::string songName);
	int play();
	int back();
	int next(); 
	int pause();
	int getCurrentTime();
	int getSongLength();
	~SongPlayer();

	private:
	int freeMusic();

};

#endif /* SONGPLAYER_H */

