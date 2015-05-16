#include "SongPlayer.h"
#include "SongLoader.h"


unsigned char *songBuffer;

SongPlayer::SongPlayer()
{

}

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
