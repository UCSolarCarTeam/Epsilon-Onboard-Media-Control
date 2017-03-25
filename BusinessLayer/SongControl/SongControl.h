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


namespace Ui
{
    class SongControl;
}

class SongControl
{
public:
    SongControl();
    bool song_exists();
    void io_event(int io_command);
    std::string next_song();
    std::string previous_song();
    std::string current_song();
    std::string libraryLoad();

private:
    Ui::SongControl *ui;
    std::vector<std::string> files = std::vector<std::string>();
    int current_song_index;
    bool check_library;
    bool read_song_names(std::string dir, std::vector<std::string> &files);
};
