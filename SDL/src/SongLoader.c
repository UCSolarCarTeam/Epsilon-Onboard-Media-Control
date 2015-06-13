#include "SongLoader.h"


SongLoader::SongLoader()
{
    counter=0;
    song=-1;
    readSongNames();
}

int SongLoader::readSongNames()
{
    
    DIR *dir;
    struct dirent *ent;
    // Change string to directory with songs in it
    if ((dir = opendir("SongLibrary")) != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            
            if (ent->d_name[0] != '.')
            {
                container.push_back(ent->d_name);
                counter++;
                }
            
        }
    }
    
    return 0;
}

int SongLoader::shuffleSongNames()
{
    
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle ( container.begin(), container.end(), g );
    song=-1;
    return 0;
}


const char* SongLoader::nextSong()
{
    song++;
    CurrentSong=container[song];
    if(song>=(counter-1))
        shuffleSongNames();
    
    return CurrentSong.c_str();
}

const char* SongLoader::previousSong()
{
    if(song<=0)
    {
        song=counter;
    }
    song--;
    CurrentSong=container[song];

    return CurrentSong.c_str();
}












