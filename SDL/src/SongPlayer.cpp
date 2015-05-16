#include "SongPlayer.h"
#include "SongLoader.h"


unsigned char *songBuffer;

SongPlayer::SongPlayer()
{
	SongLoader loader(); 
}

//Will load the songName into buffer
int SongPlayer::load(std::string songName)
{

}

int SongPlayer::play()
{

}
int SongPlayer::back()
{

}
int SongPlayer::next()
{
	load(loader.nextSong());
}
int SongPlayer::pause()
{

}
int SongPlayer::getCurrentTime()
{

}
int SongPlayer::getSongLength()
{

}

int SongPlayer::freeMusic()
{

}

SongPlayer::~SongPlayer()
{
	freeMusic();
}
