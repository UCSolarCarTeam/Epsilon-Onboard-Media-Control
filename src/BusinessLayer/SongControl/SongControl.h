#pragma once
#include <QString>
#include <QTime>
#include <QVector>

namespace Ui
{
    class SongControl;
}

class SongControl
{
public:
    SongControl();
    ~SongControl();
    bool songExists();
    QString nextSong();
    QString previousSong();
    QString currentSong();
    QString shuffleSong();
    QString libraryLoad();
    bool hasSuffix(const QString& s, const QString& suffix);

private:
    QTime startTime_;
    QVector<QString> files_;
    int currentSongIndex_;
    bool readSongNames(QString dir, QVector<QString>& files);
};
