#ifndef MUSICBAR_H
#define MUSICBAR_H

#include "SongPlayer.h"
//#include "SDL.h"
//#include <SDL2/SDL_TTF.h>
//#include <string>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL_ttf.h>
#include <iostream>
#include <sstream>
//#include <cstdlib>


class MusicBar
{
    SDL_Surface* surface;
   // SDL_Renderer* renderer;
    void drawSongName();
    void drawSongTime();  
    void drawVolumeBar();
    TTF_Font *song_name_font;
    TTF_Font *time_font;
    int init();
    SongPlayer *mPlayer;

public:
    void update();
    MusicBar(SongPlayer *songPlayer);
    SDL_Surface* returnMusicBar();

};


#endif
