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
#include <SDL2/SDL_ttf.h>

class MusicBar
{
private:

    struct timeValue {
        int mins;
        int secs;
    };
   
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
    void updateTimeBar(double songCurrentTime, double songLengthTime);
    void updateVolumeBar();

    SDL_Surface* createTimeSurface(timeValue& songTime, SDL_Rect& surfaceRect);
    int drawSurface(SDL_Surface *surface, const SDL_Rect *srcRect, SDL_Rect& destRect, int r, int g, int b);
 
public:
    
    MusicBar();
    MusicBar(SongPlayer *songPlayer);
    void update();
    SDL_Surface* returnMusicBar();

};
#endif
