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
    SDL_Surface* surface;
    void drawSongName();
    void drawTime();  
    TTF_Font *font;
    int init();
    SongPlayer mPlayer;

public:
    MusicBar(SongPlayer);
    SDL_Surface* returnMusicBar();

};


#endif
