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
#include <QVector>
#include <QFileInfo>
#include <QDebug>

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
    QVector<QString> files_;
    int currentSongIndex_;
    bool readSongNames(QString dir, QVector<QString>& files);
};
