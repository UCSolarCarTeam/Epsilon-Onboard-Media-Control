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
private:
    SDL_Surface* surface;
    TTF_Font *songNameFont;
    TTF_Font *timeFont;
    SongPlayer *mPlayer;
    
    void drawSongName();
    void drawSongTime();  
    void drawVolumeBar();
    std::string convertToString(int songIntTime);
    void setFont(TTF_Font** musicBarFont, int FontSize);
    void createGeometricSurface(SDL_Surface* geometricSurface, int surfaceWidth, int surfaceHeight, SDL_Rect surfaceLocation, int surfaceRed, int surfaceGreen, int surfaceBlue);
    int init();

    int musicbarSurfaceWidth;
    int musicbarSurfaceHeight;
    int longSongNameLocation;
    double songTimeMark;
    bool getTimeInit;
    bool longSongNameInit;

public:
    void update();
    MusicBar(SongPlayer *songPlayer);
    SDL_Surface* returnMusicBar();

};

#endif
