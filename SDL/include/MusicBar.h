#ifndef MUSICBAR_H
#define MUSICBAR_H

#include "SongPlayer.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL_ttf.h>
#include <iostream>
#include <sstream>


class MusicBar
{
    SDL_Surface* surface;
    TTF_Font *songNameFont;
    TTF_Font *timeFont;
    SongPlayer *mPlayer;
    
    void drawSongName();
    void drawSongTime();  
    void drawVolumeBar();
    std::string convertToString(int songIntTime);
    int init();

    int musicbarSurfaceWidth;
    int musicbarSurfaceHeight;
    int xSongLocation;
    double songTimeMark;
    bool getTimeInitialization;
    bool initialization;

public:
    void update();
    MusicBar(SongPlayer *songPlayer);
    SDL_Surface* returnMusicBar();

};

#endif
