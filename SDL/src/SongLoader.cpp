#include "SongLoader.h"


SongLoader::SongLoader()
{
    counter=0;
    song=-1;
    readSongNames();
    shuffleSongNames();
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
    if (counter != 0)
    {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle ( container.begin(), container.end(), g );
        song=-1;
        return 0;
    }
    return 1;
}


std::string SongLoader::nextSong()
{
    song++;
    CurrentSong=container[song];
    if(song>=(counter-1))
        shuffleSongNames();
    if (counter == 0)
        return "";
    return ("SongLibrary/" + CurrentSong);
}

std::string SongLoader::previousSong()
{
    if(song<=0)
    {
        song=counter-1;
    }
    song--;
    CurrentSong=container[song];
    if (counter == 0)
        return "";
    return ("SongLibrary/" + CurrentSong);
}

std::string SongLoader::currentSong()
{
    if (song == -1)
        song++;
    if (counter == 0)
        return "";
    return ("SongLibrary/" + container[song]);
}











