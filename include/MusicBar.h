/**
 *  Schulich Delta OnBoard Media Control
 *  Copyright (C) 2015 University of Calgary Solar Car Team
 *
 *  This file is part of the Schulich Delta OnBoard Media Control
 *
 *  The Schulich Delta OnBoard Media Control is free software: 
 *  you can redistribute it and/or modify it under the terms 
 *  of the GNU Affero General Public License as published by 
 *  the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  The Schulich Delta OnBoard Media Control is distributed 
 *  in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
 *  without even the implied warranty of MERCHANTABILITY or 
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Affero 
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General 
 *  Public License along with the Schulich Delta OnBoard Media 
 *  Control.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  For further contact, email <software@calgarysolarcar.ca>
 */

#ifndef MUSICBAR_H
#define MUSICBAR_H

#include "SongPlayer.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <sstream>
#include <string>


class MusicBar
{
private:

    #if 0 // to removed
    struct surfaceValue {
        int sX;
        int sY;
        int sW;
        int sH;
    };
    #endif

    struct timeValue {
        int mins;
        int secs;
    };
   
    #if 0
    struct charTimeValue {
        char cMins;
        char cSecs;
    };
    #endif

    SDL_Surface *musicbarSurface;
    SongPlayer *musicPlayer;
    TTF_Font *songNameFont;
    TTF_Font *timeFont;

    int songCurrentTime;
    int songLengthTime;

    void init();
    void drawMusicBar();
    void initTTF();
    void drawSongBar();
    void drawVolumeBGBar();
    void updateSongName();
    void updateSongTime();
    void updateTimeBar(timeValue* songTime);
    void updateVolumeBar();

    SDL_Surface* createTimeSurface(timeValue& songTime, SDL_Rect& surfaceRect);
    SDL_Surface drawSurface(SDL_Surface *surface, const SDL_Rect *srcRect, SDL_Rect& destRect, int r, int g, int b);
 
 /*    
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
*/
public:
    void update();
    MusicBar();
    MusicBar(SongPlayer *songPlayer);
    SDL_Surface* returnMusicBar();

};


#endif
