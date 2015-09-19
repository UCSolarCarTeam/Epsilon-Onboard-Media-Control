#ifndef MUSICBAR_H
#define MUSICBAR_H

#include "SongPlayer.h"
#include "SDL.h"
//#include <SDL2/SDL_TTF.h>
#include <string>
#include <SDL2/SDL.h>
#include <stdio.h>

#include <cstdlib>


class MusicBar
{
    SDL_Surface* surface;
    void drawSongName();
    
public:
    MusicBar();

    SDL_Surface* returnMusicBar();

};


#endif
