#include "SongPlayer.h"
#include "SongLoader.h"


SongPlayer::SongPlayer()
{
//	SongLoader loader(); 
	playing = false;
}

//Will load the songName into buffer
int SongPlayer::load(std::string songName)
{

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

}
int SongPlayer::getSongLength()
{

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



// int SongPlayer::songThread()
// {
// 	while (true)
// 	{
// 		if (playing)
// 		{
// 			if (mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK)
//         		ao_play(dev, (char*)buffer, done);
// 		}
// 	}
// }