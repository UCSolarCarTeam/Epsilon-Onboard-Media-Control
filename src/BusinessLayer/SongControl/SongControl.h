#pragma once

#include <QObject>
#include <algorithm>
#include <dirent.h>
#include <errno.h>
#include <iostream>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <QString>
#include <QTime>
#include <QVector>
#include <QFileInfo>
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
    QVector<QString> getFiles();
    bool hasSuffix(const QString& s, const QString& suffix);

private:
    QTime startTime_;
    QVector<QString> files_;
    int currentSongIndex_;
    bool readSongNames(QString dir, QVector<QString>& files);
};
