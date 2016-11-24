#pragma once

#include <string>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <random>

#include <QObject>

namespace Ui
{
class SongLoader;
}

class SongLoader
{

public:
    SongLoader();
    bool song_exists();
    std::string next_song_name();
    std::string previous_song_name();
    void io_event(int io_command);
    std::string next_song();
    std::string previous_song();
    std::string current_song();
    std::string libraryLoad();

private:
    Ui::SongLoader *ui;
    std::vector<std::string> files = std::vector<std::string>();
    int current_song_index;
    bool check_library;
    bool read_song_names(std::string dir, std::vector<std::string> &files);
    void notify_listeners(std::string song_path);
};
