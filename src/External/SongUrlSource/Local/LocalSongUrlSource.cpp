#include <QDir>
#include <QString>

#include "LocalSongUrlSource.h"

namespace
{
    const QString SONG_DIRECTORY = "/Music/SongLibrary";
}

LocalSongUrlSource::LocalSongUrlSource() : songList_()
{
    loadSongs();
}

LocalSongUrlSource::~LocalSongUrlSource()
{
}

QList<QUrl> LocalSongUrlSource::getSongList()
{
    return songList_;
}

void LocalSongUrlSource::loadSongs()
{
    QString localSongLibrary = QDir::homePath() + SONG_DIRECTORY;
    QDir songDir(localSongLibrary);
    QStringList songFileList = songDir.entryList(QStringList() << "*.mp3", QDir::Files);

    foreach (QString song, songFileList)
    {
        songList_ << QUrl::fromLocalFile(songDir.absoluteFilePath(song));
    }
}
