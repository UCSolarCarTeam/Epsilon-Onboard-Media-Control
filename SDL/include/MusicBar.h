#ifndef MUSICBAR_H
#define MUSICBAR_H

#include "SongPlayer.h"
#include "SDL.h"
//#include <SDL2/SDL_TTF.h>
#include <string>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL_ttf.h>
#include <iostream>
#include <sstream>
#include <cstdlib>


class MusicBar
{
    int xL = 0;
    int udate = 0;
    SDL_Surface* surface = NULL;
    SDL_Renderer* renderer =  NULL;
    void drawSongName();
    void drawTime();  
    void drawVolumeBar();
    TTF_Font *font;
    int init();
    SongPlayer *mPlayer;

public:
    void update();
    MusicBar(SongPlayer *songPlayer);
    SDL_Surface* returnMusicBar();

};


#endif
