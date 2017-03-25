#include "SongControl.h"

SongControl::SongControl()
{
    std::string dir = std::string(".");
    read_song_names(dir, files);
    current_song_index = 0;
}


std::string SongControl::next_song()
{
    current_song_index = (current_song_index + 1) % files.size();
    return files[current_song_index];
}

std::string SongControl::previous_song()
{
    current_song_index = (current_song_index - 1) % files.size();
    return files[current_song_index];
}

std::string SongControl::current_song()
{
    return (files[(current_song_index) % files.size()]);
}

void SongControl::io_event(int io_command)
{
    switch (io_command)
    {
    case 1:
        next_song();

    case 2:
        previous_song();
    }
}

bool has_suffix(const std::string& s, const std::string& suffix)
{
    return (s.size() >= suffix.size()) && equal(suffix.rbegin(), suffix.rend(), s.rbegin());
}

bool SongControl::read_song_names(std::string dir, std::vector<std::string> &files)
{
    DIR *dp;
    std::string filepath;
    dir = "/home/ben/Music";
    struct dirent *dirp;
    if ((dp = opendir("/home/ben/Music")) == NULL)
    {
        return false;
    }
    
    while ((dirp = readdir(dp)) != NULL)
    {
        if (has_suffix(dirp->d_name, ".mp3"))
        {
            filepath = dir + "/" + dirp->d_name;
            files.push_back(std::string(filepath));
        }
    }
    closedir(dp);
    return true;
}
