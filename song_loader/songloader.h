#ifndef SONGLOADER_H
#define SONGLOADER_H

#include <string>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <iostream>
#include <stdio.h>
#include "I_song_loader_observer.h"
//#include "I_io_event_observer.h"
#include "Observable.h"
//#include "config.h"
#include <algorithm>
#include <vector>
#include <random>

#include <QMainWindow>

namespace Ui {
class SongLoader;
}

class SongLoader : public QMainWindow, public Observable<I_SongLoaderObserver>//,public I_IoEventObserver
{
    Q_OBJECT

public:
    explicit SongLoader(QWidget *parent = 0);
    ~SongLoader();
    bool song_exists();
    void next_song_name();
    void previous_song_name();
    void io_event(int io_command);
    void next_song();
    void previous_song();
    void shuffle_songs();
    void current_song();
    int libraryLoad();

private:
    Ui::SongLoader *ui;
    std::vector<std::string> files =std::vector<std::string>();
    int current_song_index;
    bool check_library;
    bool read_song_names(std::string dir, std::vector<std::string> &files);
    void notify_listeners(std::string song_path);
};

#endif // SONGLOADER_H
