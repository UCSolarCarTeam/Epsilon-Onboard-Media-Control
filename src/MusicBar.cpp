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

#include "MusicBar.h"

// ************ CONSTRUCTORS ****************

// if no songs default constructor
MusicBar::MusicBar()   
{
    init();
    drawMusicBar();
}

// if there is songs call constructor
MusicBar::MusicBar(SongPlayer *songPlayer)
{
    musicPlayer = songPlayer; 
    init();
}

// ************** INITIALIZATION ***********

void MusicBar::init()
{
    drawMusicBar();
    initTTF();
}

void MusicBar::drawMusicBar()
{
    SDL_Rect musicBarRect = {0, 0, 1080, 64};
    musicbarSurface = SDL_CreateRGBSurface(0, musicBarRect.w, musicBarRect.h, 32, 0, 0, 0, 0); 
}

void MusicBar::initTTF()
{
    if (TTF_Init() != 0)
    {
        fprintf(stderr, "ERROR: TTF_Init Failed: %s \n", TTF_GetError());
        SDL_Quit();
        exit(1);
    }

    if (!(songNameFont = TTF_OpenFont("/usr/share/fonts/ArialUni.ttf", 45)))
    {
        fprintf(stderr, "ERROR TTF_OpenFont songNameFont Failed: %s \n", TTF_GetError());
        TTF_Quit();
        SDL_Quit();
        exit(1);
    }

    if (!(timeFont = TTF_OpenFont("/usr/share/fonts/ArialUni.ttf", 25)))
    {
        fprintf(stderr, "ERROR TTF_OpenFont timeFont Failed: %s \n", TTF_GetError());
        TTF_Quit();
        SDL_Quit();
        exit(1);
    }
}

// ************** FEATURE FUNCTIONS ************

void MusicBar::drawSongBar()
{
    SDL_Surface *songBarSurface = NULL;
    SDL_Rect songBarRect = {150, 6, 700, 52};

    drawSurface(songBarSurface, NULL, songBarRect, 35, 35, 35); 
}

void MusicBar::drawVolumeBGBar()
{
    SDL_Surface *volBGBarSurface = NULL;
    SDL_Rect volBGBarRect = {880, 50, 4, 4};
    int volBarNumber = 20;
    
    for (int i = 0; i < volBarNumber; i++)
    {
        drawSurface(volBGBarSurface, NULL, volBGBarRect, 0, 0, 0);

        volBGBarRect.x += 6;  
        volBGBarRect.y -= 2;
        volBGBarRect.h += 2;
    }
}

void MusicBar::updateSongName() 
{

    std::string strSongName = musicPlayer->currentSong();
    size_t strSongLength = strSongName.length() - strlen("/home/Music/") - strlen(".mp3");
    strSongName = strSongName.substr(strlen("/home/Music/"), strSongLength); 
    const char *songName = strSongName.c_str();

    SDL_Surface *songNameSurface = NULL;
    SDL_Color songColor = {255, 255, 255};
    
    SDL_Rect songNameRect = {150, 0, 0, 0};
    
    if (!(songNameSurface = TTF_RenderUTF8_Blended(songNameFont, songName, songColor))) 
    {
        fprintf(stderr, "ERROR: TTF_RenderUTF8_Blended songNameSurface Failed: %s \n", TTF_GetError());
    }   

    TTF_SizeText(songNameFont, songName, &songNameRect.w, &songNameRect.h);

    songNameRect.y = 64/2 - songNameRect.h/2;

    SDL_Rect songNameSrcRect = {0, 0, 700, songNameRect.h};


    drawSurface(songNameSurface, &songNameSrcRect, songNameRect, 0, 0, 0);
}
void MusicBar::updateSongTime()
{
    songCurrentTime = musicPlayer->getCurrentTime(); 
    songLengthTime = musicPlayer->getSongLength(); 
    timeValue currentTime = {songCurrentTime / 60, songCurrentTime % 60};
    timeValue lengthTime = {songLengthTime / 60, songLengthTime % 60};

    SDL_Rect songCurrentTimeRect = {0, 4, 0, 0};
    SDL_Surface* songCurrentTimeSurface = createTimeSurface(currentTime, songCurrentTimeRect);
    
    drawSurface(songCurrentTimeSurface, NULL, songCurrentTimeRect, 0, 0, 0);

    SDL_Rect songLengthTimeRect = {0, 4, 0, 0};
    SDL_Surface* songLengthTimeSurface = createTimeSurface(lengthTime, songLengthTimeRect);
    songLengthTimeRect.x = 1080 - songLengthTimeRect.w;

    drawSurface(songLengthTimeSurface, NULL, songLengthTimeRect, 0, 0, 0);

    updateTimeBar(songCurrentTime, songLengthTime);
}
void MusicBar::updateTimeBar(double songCurrentTime, double songLengthTime)
{
    SDL_Surface* songTimeBGBarSurface = NULL;
    SDL_Rect songTimeBGBarRect = {0, 0, 1080, 3};

    if (drawSurface(songTimeBGBarSurface, NULL, songTimeBGBarRect, 0, 0, 0))
        fprintf(stderr, "Failed to draw songTimeBGBarSurface\n");



    SDL_Surface* songTimeBarSurface = NULL;
    double songTimePercent = songCurrentTime / songLengthTime;
    SDL_Rect songTimeBarRect = {0, 0, 0 + songTimePercent*1080, 3};

    drawSurface(songTimeBarSurface, NULL, songTimeBarRect, 0, 162, 255);

}


void MusicBar::updateVolumeBar()
{
    int volBarNumber = 20;
    double songMaxVol = 0.4;
    double songCurrentVol = musicPlayer->getVolume();
    double songPercentVol = (songCurrentVol / songMaxVol) *volBarNumber - 0.1;
    int green = 162;
    SDL_Surface* volBarSurface = NULL;
    
    SDL_Rect volBarRect = {880, 50, 4, 4};

    for (int i = 0; i < songPercentVol; i++)
    {
        drawSurface(volBarSurface, NULL, volBarRect, 255, green, 0);

        volBarRect.x += 6;
        volBarRect.y -= 2;
        volBarRect.h += 2;
        green -= 8;
    }

}
    
// ********* MAIN FUNCTIONS ***********

void MusicBar::update()
{ 
    SDL_FillRect(musicbarSurface, NULL, SDL_MapRGB(musicbarSurface->format,43,43,43)); 
    drawSongBar();
    drawVolumeBGBar();
    
    updateSongName();
    updateSongTime();
    updateVolumeBar(); 
}

SDL_Surface* MusicBar::returnMusicBar()
{
    return musicbarSurface;
}

// ******** HELPER FUNCTIONS ***********


SDL_Surface* MusicBar::createTimeSurface(timeValue& songTime, SDL_Rect& surfaceRect) 
{
    const char * cSongTime;

    if (songTime.secs < 10)
        cSongTime = (std::to_string(songTime.mins) + ":0" + std::to_string(songTime.secs)).c_str();
    else
        cSongTime = (std::to_string(songTime.mins) + ":" + std::to_string(songTime.secs)).c_str();

    TTF_SizeText(timeFont, cSongTime, &surfaceRect.w, &surfaceRect.h);
    

    SDL_Surface *songTimeSurface;
    SDL_Color songTimeColor = {255, 255, 255};
    if (!(songTimeSurface = TTF_RenderText_Blended(timeFont, cSongTime, songTimeColor))) 
    {
        fprintf(stderr, "ERROR: TTF_RenderUTF8_Blended songTimeSurface Failed: %s \n", TTF_GetError());
    }   
    TTF_SizeText(timeFont, cSongTime, &surfaceRect.w, &surfaceRect.h);

    return songTimeSurface;
}
int MusicBar::drawSurface(SDL_Surface *surface, const SDL_Rect *srcRect, SDL_Rect& destRect, int r, int g, int b) 
{
    if (surface == NULL) 
    {
        surface = SDL_CreateRGBSurface(0, destRect.w, destRect.h, 32, 0, 0, 0, 0);
        if (surface == NULL)
            fprintf(stderr, "CreateRGBSurface failed: %s\n", SDL_GetError());
        SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, r, g, b));
    }
    if (srcRect != NULL)
    {
        if (SDL_BlitSurface(surface, &(*srcRect), musicbarSurface, &destRect))
            fprintf(stderr, "BlitSurface failed: %s\n", SDL_GetError());
    }
    else
    {
        if (SDL_BlitSurface(surface, &(*srcRect), musicbarSurface, &destRect))
            fprintf(stderr, "BlitSurface failed: %s\n", SDL_GetError());
    }
    SDL_FreeSurface(surface);
    surface = NULL;

    return 0;
}
