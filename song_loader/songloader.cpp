#include "songloader.h"
#include "ui_songloader.h"



SongLoader::SongLoader(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SongLoader)
{
    std::string dir = std::string(".");
    ui->setupUi(this);
}

SongLoader::~SongLoader()
{
    delete ui;
}

void SongLoader::notify_listeners(std::string song_path)
{
    for(I_SongLoaderObserver*listener:listeners)
    {
        listener->current_song(song_path);
    }
}

void SongLoader::next_song()
{
    current_song_index = (current_song_index + 1)%files.size();
    notify_listeners(files[current_song_index]);
}

void SongLoader::previous_song()
{
    current_song_index = (current_song_index - 1)%files.size();
    notify_listeners(files[current_song_index]);
}

void SongLoader::next_song_name()
{
    notify_listeners(files[(current_song_index + 1)%files.size()]);
}

void SongLoader::previous_song_name()
{
    notify_listeners(files[(current_song_index - 1)%files.size()]);
}

void SongLoader::current_song()
{
    notify_listeners(files[(current_song_index)%files.size()]);
}

void SongLoader::io_event(int io_command)
{
    switch(io_command)
    {
        case 1:
            next_song();

        case 2:
            previous_song();

        case 3:
            next_song_name();

        case 4:
            previous_song_name();
    }
}

bool has_suffix(const std::string& s, const std::string& suffix)
{
    return(s.size() >= suffix.size()) && equal(suffix.rbegin(), suffix.rend(), s.rbegin());
}

bool SongLoader::read_song_names(std::string dir, std::vector<std::string> &files)
{
   DIR *dp;
   std::string filepath;
   dir = "/home/Music";
   struct dirent *dirp;
   if((dp  = opendir("/home/Music")) == NULL)
   {
       return false;
   }

   while ((dirp = readdir(dp)) != NULL)
   {
        if(has_suffix(dirp->d_name, ".mp3"))
        {
             filepath = dir + "/" + dirp->d_name;
             files.push_back(std::string(filepath));
        }
   }
   closedir(dp);
   return true;
}

