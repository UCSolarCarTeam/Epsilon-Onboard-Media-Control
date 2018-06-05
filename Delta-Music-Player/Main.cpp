#include "SongLoader.h"
#include "SongPlayer.h"

#include <stdio.h>

int noSongs;
SongPlayer musicPlayer;


void signalToQuit();
void close();


void signalToQuit()
{
    musicPlayer.songQuit();
}

void close()
{
    musicPlayer.closeSongPlayer();
    exit(0);
}

int main(int argc, char* argv[])
{

    if (musicPlayer.initSongPlayer())
    {
        noSongs = true;
        fprintf(stderr, "No SongLibrary Folder! Not creating Music Thread!\n");
    }
    else
    {
        musicPlayer.StartThread();
    }

    musicPlayer.WaitForThreadToExit();
    return 0;
}