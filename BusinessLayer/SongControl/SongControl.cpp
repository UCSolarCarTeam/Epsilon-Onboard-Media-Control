#include <QDir>
#include "SongControl.h"

SongControl::SongControl()
{
    files_ = QVector<QString>();
    playOrder_ = QVector<int>(10, -1);
    QString dir = QString(".");
    readSongNames(dir, files_);
    currentSongIndex_ = 0;
    prevSongIndex_ = 0;
}

SongControl::~SongControl()
{
}

QString SongControl::nextSong()
{
    currentSongIndex_ = (currentSongIndex_ + 1) % files_.size();
    playOrder_.prepend(currentSongIndex_);
    prevSongIndex_ = 0;
    return files_[currentSongIndex_];
}

QString SongControl::previousSong()
{

    if (prevSongIndex_ < 9)
    {
        prevSongIndex_ += 1;
    }

    if (playOrder_[prevsSongIndex_] == -1)
    {
        currentSongIndex_ -= 1;
        if (currentSongIndex_ < 0)
        {
            currentSongIndex_ = files_.size() - 1;
        }
        return files_[currentSongIndex_];
    }

    return files_[playOrder_[prevSongIndex_]];
}

QString SongControl::currentSong()
{
    playOrder_.prepend(currentSongIndex_);
    prevSongIndex_ = 0;
    return (files_[(currentSongIndex_)]);
}

QString SongControl::shuffleSong()
{
    currentSongIndex_ = (rand() % files_.size());
    playOrder_.prepend(currentSongIndex_);
    prevSongIndex_ = 0;
    return (files_[currentSongIndex_]);
}

bool SongControl::hasSuffix(const QString& s, const QString& suffix)
{
    //compare returns 0 when the two strings are equal
    if (QString::compare(s.right(4), suffix) == 0)
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

    QDir relativeDirectory(".");
    if (!relativeDirectory.cdUp())
    {
        return false;
    }
    if (!relativeDirectory.cd("Epsilon-Onboard-Media-Control/DataLayer/SongLibrary"))
    {
        return false;
    }

    dir = relativeDirectory.absolutePath();

    QByteArray array = dir.toLocal8Bit();   //converting QString to char*
    char* dirCharPointer = array.data();

    struct dirent* dirp;

    if ((dp = opendir(dirCharPointer)) == NULL)
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
