#include "SongControl.h"

SongControl::SongControl()
{
    QString dir = QString(".");
    readSongNames(dir, files_);
    current_song_index_ = 0;
}


QString SongControl::nextSong()
{
    current_song_index_ = (current_song_index_ + 1) % files_.size();
    return files_[current_song_index_];
}

QString SongControl::previousSong()
{
    current_song_index_ = (current_song_index_ - 1) % files_.size();
    return files_[current_song_index_];
}

QString SongControl::currentSong()
{
    return (files_[(current_song_index_) % files_.size()]);
}

void SongControl::ioEvent(int io_command)
{
    switch (io_command)
    {
        case 1:
            nextSong();

        case 2:
            previousSong();
    }
}

bool SongControl::hasSuffix(const QString& s, const QString& suffix)
{
    if (0 == QString::compare(s.right(4), suffix))
    {

        return true;
    }
    else
    {
        return false;
    }
}

bool SongControl::readSongNames(QString dir, QVector<QString>& files_)
{
    DIR* dp;
    QString filepath;
    dir = "/home/ben/Music";
    struct dirent* dirp;

    if ((dp = opendir("/home/ben/Music")) == NULL)
    {
        return false;
    }

    while ((dirp = readdir(dp)) != NULL)
    {
        if (hasSuffix(dirp->d_name, ".mp3"))
        {
            filepath = dir + "/" + dirp->d_name;
            files_.push_back(QString(filepath));
        }
    }

    closedir(dp);
    return true;
}
