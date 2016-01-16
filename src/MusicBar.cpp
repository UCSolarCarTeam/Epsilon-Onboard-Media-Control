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
    musicPlayer = songPlayer; // C-Var
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
    //surfaceValue musicBarValue = {0, 0, 1080, 64};
    musicbarSurface = SDL_CreateRGBSurface(0, musicBarRect.w, musicBarRect.h, 32, 0, 0, 0, 0); // C Value
    # if 0
    SDL_FillRect(musicbarSurface, NULL, SDL_MapRGB(musicbarSurface->format,43,43,43)); 
    drawSongBar();
    drawVolumeBGBar();
    #endif
}

#if 1
void MusicBar::initTTF()
{
    if (TTF_Init() != 0)
    {
        fprintf(stderr, "ERROR: TTF_Init Failed: %s \n", TTF_GetError());
        SDL_Quit();
        exit(1);
    }

    if (!(songNameFont = TTF_OpenFont("/usr/share/fonts/ArialUni.ttf", 45))) // C-Var
    {
        fprintf(stderr, "ERROR TTF_OpenFont songNameFont Failed: %s \n", TTF_GetError());
        TTF_Quit();
        SDL_Quit();
        exit(1);
    }

    if (!(timeFont = TTF_OpenFont("/usr/share/fonts/ArialUni.ttf", 25))) // C-Var
    {
        fprintf(stderr, "ERROR TTF_OpenFont timeFont Failed: %s \n", TTF_GetError());
        TTF_Quit();
        SDL_Quit();
        exit(1);
    }
}
#endif

// ************** FEATURE FUNCTIONS ************

#if 1
void MusicBar::drawSongBar()
{
    SDL_Surface *songBarSurface = NULL;
    SDL_Rect songBarRect = {150, 6, 700, 52};
    //surfaceValue songBarValue = {150, 6, 700, 52};

    drawSurface(songBarSurface, NULL, songBarRect, 35, 35, 35); 
}
#endif

#if 1
void MusicBar::drawVolumeBGBar()
{
    SDL_Surface *volBGBarSurface = NULL;
    SDL_Rect volBGBarRect = {880, 50, 4, 4};
    //surfaceValue volBGBarValue = {880, 50, 4, 4};
    int volBarNumber = 20;
    
    for (int i = 0; i < volBarNumber; i++)
    {
        drawSurface(volBGBarSurface, NULL, volBGBarRect, 0, 0, 0);

        volBGBarRect.x += 6;  // volBgBarVaue.surfaceX
        volBGBarRect.y -= 2;
        volBGBarRect.h += 2;
    }
}
#endif 
#if 1
void MusicBar::updateSongName() 
{
    #if 0
    SDL_Surface *some_surface;
    SDL_Rect some_surface_loc = {0,0,800,64};
    some_surface = SDL_CreateRGBSurface(0, 1080, 64, 32, 0, 0, 0, 0);
    SDL_FillRect(some_surface, NULL, SDL_MapRGB(some_surface->format, 80, 0, 0));
    SDL_BlitSurface(some_surface, NULL, musicbarSurface, &some_surface_loc);
    #endif

    #if 1
    std::string strSongName = musicPlayer->currentSong();
    //size_t strSongLength = strSongName.length() - strSongName.find_last_of("/Music/") - sizeof(".mp3");
    size_t strSongLength = strSongName.length() - strlen("/home/Music/") - strlen(".mp3");
    strSongName = strSongName.substr(strlen("/home/Music/"), strSongLength); 
    const char *songName = strSongName.c_str();
    #endif

    #if 0
    std::string strSongName = musicPlayer->currentSong();
    size_t strSongLength = strSongName.length(); 
    strSongName = strSongName.substr(12, strSongLength - 16); // removes SongLibrary/ and .mp3 from songName
    const char *songName = strSongName.c_str();
    #endif

    SDL_Surface *songNameSurface = NULL;
    SDL_Color songColor = {255, 255, 255};
    
    SDL_Rect songNameRect = {150, 0, 0, 0};
    //surfaceValue songNameValue = {150, 0, 0, 0};
    
    if (!(songNameSurface = TTF_RenderUTF8_Blended(songNameFont, songName, songColor))) 
    {
        fprintf(stderr, "ERROR: TTF_RenderUTF8_Blended songNameSurface Failed: %s \n", TTF_GetError());
    }   

    TTF_SizeText(songNameFont, songName, &songNameRect.w, &songNameRect.h);

    songNameRect.y = 64/2 - songNameRect.h/2;

    SDL_Rect songNameSrcRect = {0, 0, 700, songNameRect.h};

    #if 0 // EDIT FUNCTIONS TO ACCOMDATE A SRCRECT
    SDL_Rect songNameSrcRect = {0,0,800,songNameRect.h};
    SDL_BlitSurface(songNameSurface, &songNameSrcRect, musicbarSurface, &songNameRect);
    #endif

    drawSurface(songNameSurface, &songNameSrcRect, songNameRect, 0, 0, 0);
}
#endif
#if 1
void MusicBar::updateSongTime()
{
    songCurrentTime = musicPlayer->getCurrentTime(); // CLASS VARIABLE
    songLengthTime = musicPlayer->getSongLength(); // CLASS VARIABLE
    timeValue currentTime = {songCurrentTime / 60, songCurrentTime % 60};
    timeValue lengthTime = {songLengthTime / 60, songLengthTime % 60};

    SDL_Rect songCurrentTimeRect = {0, 4, 0, 0};
    SDL_Surface* songCurrentTimeSurface = createTimeSurface(currentTime, songCurrentTimeRect);
    
    drawSurface(songCurrentTimeSurface, NULL, songCurrentTimeRect, 0, 0, 0);

    #if 1
    SDL_Rect songLengthTimeRect = {0, 4, 0, 0};
    SDL_Surface* songLengthTimeSurface = createTimeSurface(lengthTime, songLengthTimeRect);
    songLengthTimeRect.x = 1080 - songLengthTimeRect.w;

    drawSurface(songLengthTimeSurface, NULL, songLengthTimeRect, 0, 0, 0);

    updateTimeBar(songCurrentTime, songLengthTime);
    #endif
}
#endif
#if 1
void MusicBar::updateTimeBar(double songCurrentTime, double songLengthTime)
{
    SDL_Surface* songTimeBGBarSurface = NULL;
    SDL_Rect songTimeBGBarRect = {0, 0, 1080, 3};

    if (drawSurface(songTimeBGBarSurface, NULL, songTimeBGBarRect, 0, 0, 0))
        fprintf(stderr, "Failed to draw songTimeBGBarSurface\n");

    #if 0 // SEG FAULT CODE BELOW
    
    SDL_Rect songTimeBarRect = {0, 0, 80, 3};
    if (drawSurface(songTimeBarSurface, NULL, songTimeBarRect, 100, 0, 0))
        fprintf(stderr, "Failed to draw songTimeBarSurface\n");

    #endif

    #if 1

    SDL_Surface* songTimeBarSurface = NULL;
    double songTimePercent = songCurrentTime / songLengthTime;
    SDL_Rect songTimeBarRect = {0, 0, 0 + songTimePercent*1080, 3};

    drawSurface(songTimeBarSurface, NULL, songTimeBarRect, 0, 162, 255);

    #endif
}
#endif

#if 1

void MusicBar::updateVolumeBar()
{
    int volBarNumber = 20;
    double songMaxVol = 0.4;
    double songCurrentVol = musicPlayer->getVolume();
    double songPercentVol = (songCurrentVol / songMaxVol) *volBarNumber - 0.1;
    int green = 162;
    SDL_Surface* volBarSurface = NULL;
    
    SDL_Rect volBarRect = {880, 50, 4, 4};

    #if 1 // SEGFAULTS // SOLUTION: use volBGBarSurface // ASK BYRON WHY 

    for (int i = 0; i < songPercentVol; i++)
    {
        drawSurface(volBarSurface, NULL, volBarRect, 255, green, 0);

        volBarRect.x += 6;
        volBarRect.y -= 2;
        volBarRect.h += 2;
        green -= 8;
    }

    #endif
}
#endif
    
// ********* MAIN FUNCTIONS ***********

#if 1
void MusicBar::update()
{ 
    SDL_FillRect(musicbarSurface, NULL, SDL_MapRGB(musicbarSurface->format,43,43,43)); 
    drawSongBar();
    drawVolumeBGBar();
    
    updateSongName();
    updateSongTime();
    updateVolumeBar(); 
}
#endif

SDL_Surface* MusicBar::returnMusicBar()
{
    return musicbarSurface;
}

// ******** HELPER FUNCTIONS ***********


#if 1
SDL_Surface* MusicBar::createTimeSurface(timeValue& songTime, SDL_Rect& surfaceRect)  // HELPER FUNCTION
{
    const char * cSongTime;

    #if 1 
    if (songTime.secs < 10)
        cSongTime = (std::to_string(songTime.mins) + ":0" + std::to_string(songTime.secs)).c_str();
    else
        cSongTime = (std::to_string(songTime.mins) + ":" + std::to_string(songTime.secs)).c_str();
    #endif

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
#endif
#if 1
int MusicBar::drawSurface(SDL_Surface *surface, const SDL_Rect *srcRect, SDL_Rect& destRect, int r, int g, int b) // HELPER FUNCTION
{
    //SDL_Rect surfaceLocation = {values->sX, values->sY, values->sW, values->sH};
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
#endif

// ************* OLD STUFF **************


#if 0
MusicBar::MusicBar(SongPlayer *songPlayer)
{
    mPlayer = songPlayer;
    musicbarSurfaceWidth = 1080;
    musicbarSurfaceHeight = 64;
    longSongNameLocation = 150;
    getTimeInit = false;
    longSongNameInit = false;
    songTimeMark = 0;
    surface = SDL_CreateRGBSurface(0, musicbarSurfaceWidth, musicbarSurfaceHeight, 32, 0, 0, 0, 0);
    init();    
}

int MusicBar::init()
{
    int songNameFontSize; 
    int timeFontSize;
    
    songNameFontSize = 45;
    timeFontSize = 25;
   
    if (TTF_Init() !=0)
    {
        fprintf(stderr, "TTF_Init Failed%s\n", TTF_GetError());
        SDL_Quit();
        exit(1);
    }
    
    setFont(&songNameFont, songNameFontSize);
    setFont(&timeFont, timeFontSize);
    
}

void MusicBar::setFont(TTF_Font **musicBarFont, int fontSize)
{
    *musicBarFont = TTF_OpenFont("/usr/share/fonts/ArialUni.ttf", fontSize);
    if (*musicBarFont == NULL)
    {
        fprintf(stderr, "TTF_OpenFont Failed%s\n", TTF_GetError());
        TTF_Quit();
        SDL_Quit();
        exit(1);
    }
}

void MusicBar::createGeometricSurface(SDL_Surface* geometricSurface, int surfaceWidth, int surfaceHeight, SDL_Rect surfaceLocation, int surfaceRed, int surfaceGreen, int surfaceBlue)
{
    geometricSurface = SDL_CreateRGBSurface(0, surfaceWidth, surfaceHeight, 32, 0, 0, 0, 0);
    SDL_FillRect(geometricSurface, NULL, SDL_MapRGB(geometricSurface->format,surfaceRed,surfaceGreen,surfaceBlue));
    SDL_BlitSurface(geometricSurface, NULL, surface, &surfaceLocation);
    SDL_FreeSurface(geometricSurface);
}

void MusicBar::drawSongName()
{ 
    std::string songName;
    int songStringLength;
    const char * songChar;
    int songWidth;
    int songHeight;

    songName = mPlayer->currentSong();
    songStringLength = songName.length();
    songName = songName.substr(12, songStringLength - 16); // removes SongLibrary/ and .mp3 from songName
    songChar = songName.c_str(); 
    
    double songCurrentTime;
    double songScrollDelay;
    int songScrollSpeed;
    int songStartPoint;
    int songEndPoint;
    int maxSongWidth;
    int shortSongLocation;

    songScrollSpeed = 5;
    songScrollDelay = 3;
    songStartPoint = 150;
    songEndPoint = 850;
    shortSongLocation = 500;
    maxSongWidth = songEndPoint - songStartPoint;

    songCurrentTime = mPlayer->getCurrentTime();
    
    if (songCurrentTime >= 0 && songCurrentTime <= songScrollDelay)
    {
        longSongNameLocation = songStartPoint;
        longSongNameInit = false;
    }

    if (longSongNameLocation >= songEndPoint)
    {
        longSongNameInit = true;
        getTimeInit = false;
    }
   
    if (longSongNameInit == true)
    {  
        if (longSongNameLocation <= songStartPoint)
        {
            if (getTimeInit == false)
            {
                songTimeMark = songCurrentTime;
                getTimeInit = true;
            }   
            if (songCurrentTime < (songTimeMark + songScrollDelay)) 
            {
                longSongNameLocation = songStartPoint;
            }       
        }
    }
    
    // Song Background Box Surface
    SDL_Surface *songBoxSurface;
    SDL_Rect songBoxLocation = {songStartPoint, 6, 0, 0};
    
    /*songBoxSurface = SDL_CreateRGBSurface(0, maxSongWidth, 52, 32, 0, 0, 0, 0);
    SDL_FillRect(songBoxSurface, NULL, SDL_MapRGB(songBoxSurface->format,35,35,35));
    SDL_Rect songBoxLocation = {songStartPoint, 6, 0, 0};
    SDL_BlitSurface(songBoxSurface, NULL, surface, &songBoxLocation);
    SDL_FreeSurface(songBoxSurface);
    */

    createGeometricSurface(songBoxSurface, maxSongWidth, 52, songBoxLocation, 35,35,35);
    
    // Song Name Surface
    SDL_Surface *songSurface;
    SDL_Rect songLocation;
    SDL_Color songColor = {255, 255, 255}; 
    songSurface = TTF_RenderUTF8_Blended(songNameFont, songChar, songColor);
    TTF_SizeText(songNameFont, songChar, &songWidth, &songHeight);

    if (songWidth >= maxSongWidth)
    {    
        songLocation = {longSongNameLocation, musicbarSurfaceHeight/2 - songHeight/2, 0, 0}; 
        SDL_BlitSurface(songSurface, NULL, surface, &songLocation);
        SDL_FreeSurface(songSurface);
        longSongNameLocation = longSongNameLocation - songScrollSpeed;
        if (longSongNameLocation + songWidth < songStartPoint)
        {
            longSongNameLocation = songEndPoint;
        }
    } 
    else 
    {
        songLocation = {shortSongLocation - (songWidth/2), musicbarSurfaceHeight/2 - songHeight/2, 0, 0}; //880 is start of volume bar, 50 is end of current time
        SDL_BlitSurface(songSurface, NULL, surface, &songLocation);
        SDL_FreeSurface(songSurface);
    }
    
    SDL_Surface *leftMaskSurface;
    SDL_Rect leftMaskLocation = {0,0,0,0};

    SDL_Surface *rightMaskSurface;
    SDL_Rect rightMaskLocation = {songEndPoint,0,0,0};
/*
    leftMaskSurface = SDL_CreateRGBSurface(0, songStartPoint, musicbarSurfaceHeight, 32, 0, 0, 0, 0);
    SDL_FillRect(leftMaskSurface, NULL, SDL_MapRGB(leftMaskSurface->format,43,43,43));
    SDL_Rect leftMaskLocation = {0,0,0,0};
    SDL_BlitSurface(leftMaskSurface, NULL, surface, &leftMaskLocation);
    SDL_FreeSurface(leftMaskSurface);

    SDL_Surface *rightMaskSurface;
    rightMaskSurface = SDL_CreateRGBSurface(0, musicbarSurfaceWidth - songEndPoint, musicbarSurfaceHeight, 32, 0, 0, 0, 0);
    SDL_FillRect(rightMaskSurface, NULL, SDL_MapRGB(rightMaskSurface->format,43,43,43));
    SDL_Rect rightMaskLocation = {songEndPoint,0,0,0};
    SDL_BlitSurface(rightMaskSurface, NULL, surface, &rightMaskLocation);
    SDL_FreeSurface(rightMaskSurface);
*/
    createGeometricSurface(leftMaskSurface, songStartPoint, musicbarSurfaceHeight, leftMaskLocation, 43,43,43);
    createGeometricSurface(rightMaskSurface, musicbarSurfaceWidth - songEndPoint, musicbarSurfaceHeight, rightMaskLocation, 43, 43, 43);
}


std::string MusicBar::convertToString(int songIntTime)
{
    std::string songStringTime;

    std::stringstream convertSongIntTime;
    convertSongIntTime << songIntTime;
    songStringTime = convertSongIntTime.str();

    return songStringTime;
}

void MusicBar::drawSongTime()
{ 
    double songCurrentTime;
    int songCurrentMins;
    int songCurrentSecs;
    double songCurrentPercent;
    int songCurrentIntTime;
 
    std::string songCurrentStrTime;
    std::string songCurrentStrMins;
    std::string songCurrentStrSecs;
    const char * songCurrentCharTime; 

    double songTotalTime;
    int songTotalMins;
    int songTotalSecs;
    int songTotalIntTime;

    std::string songTotalStrTime;
    std::string songTotalStrMins;
    std::string songTotalStrSecs;
    const char * songTotalCharTime;

    int totalTimeWidth;
    int totalTimeHeight;

    songCurrentTime = mPlayer->getCurrentTime();
    songTotalTime = mPlayer->getSongLength();
    
    songCurrentPercent = songCurrentTime / songTotalTime; 
    songCurrentIntTime = songCurrentTime;
    songCurrentMins = songCurrentIntTime / 60; 
    songCurrentSecs = songCurrentIntTime % 60;

    //songTotalTime = songTotalTime - songCurrentTime; // Remove to stop end time increment
    songTotalIntTime = songTotalTime;
    songTotalMins = songTotalTime / 60; 
    songTotalSecs = songTotalIntTime % 60; 
    
    songCurrentStrMins = convertToString(songCurrentMins);
    songCurrentStrSecs = convertToString(songCurrentSecs);
    
    if (songCurrentSecs < 10) 
    {
        songCurrentStrTime = songCurrentStrMins + ":0" + 
                                songCurrentStrSecs;
    }
    else
    {
        songCurrentStrTime = songCurrentStrMins + ":" + songCurrentStrSecs;
    }
    
    songCurrentCharTime = songCurrentStrTime.c_str();

    songTotalStrMins = convertToString(songTotalMins);
    songTotalStrSecs = convertToString(songTotalSecs);
    
    if (songTotalSecs < 10) 
    {
        songTotalStrTime = songTotalStrMins + ":0" + songTotalStrSecs;
    }
    else
    {
        songTotalStrTime = songTotalStrMins + ":" + songTotalStrSecs;
    }

    songTotalCharTime =  songTotalStrTime.c_str();
     
    // SDL CALLS//
    
    SDL_Color songTimeColor = {255, 255, 255};
    
    SDL_Surface *songCurrentTimeSurface;
    songCurrentTimeSurface = TTF_RenderText_Blended(timeFont, songCurrentCharTime, songTimeColor);
    SDL_Rect songCurrentTimeLocation = {0, 4, 0, 0}; 
    SDL_BlitSurface(songCurrentTimeSurface, NULL, surface, &songCurrentTimeLocation);
    SDL_FreeSurface(songCurrentTimeSurface);
    
    SDL_Surface *songTotalTimeSurface;
    songTotalTimeSurface = TTF_RenderText_Blended(timeFont, songTotalCharTime, songTimeColor);
    TTF_SizeText(timeFont, songTotalCharTime, &totalTimeWidth, &totalTimeHeight);
    SDL_Rect songTotalTimeLocation = {musicbarSurfaceWidth - totalTimeWidth, 4, 0}; 
    SDL_BlitSurface(songTotalTimeSurface, NULL, surface, &songTotalTimeLocation);
    SDL_FreeSurface(songTotalTimeSurface);

    SDL_Surface *songTimebarSurface;
    SDL_Rect songTimebarLocation = {0, 0, 0, 0};
    /*
    songTimebarSurface = SDL_CreateRGBSurface(0, 0 + songCurrentPercent*musicbarSurfaceWidth, 3, 32, 0, 0, 0, 0); 
    SDL_FillRect(songTimebarSurface, NULL, SDL_MapRGB(songTimebarSurface->format,0,162,255));
    SDL_Rect songTimebarLocation = {0, 0, 0, 0};
    SDL_BlitSurface(songTimebarSurface, NULL, surface, &songTimebarLocation);
    SDL_FreeSurface(songTimebarSurface);
    */
    
    createGeometricSurface(songTimebarSurface,
            0 + songCurrentPercent*musicbarSurfaceWidth,
            3,
            songTimebarLocation,
            0,162,255);
}

void MusicBar::drawVolumeBar()
{
    double songVolumeCurrent;
    double songVolumePercent;
    double songVolumeMax;
    songVolumeMax = 0.4;

    songVolumeCurrent = mPlayer->getVolume();
    
    songVolumePercent = songVolumeCurrent / songVolumeMax;
    
    // Volume Background Bar
    SDL_Surface *volumeBackgroundSurface;
    int volumeBarHeight;
    int volumeBarXLocation;
    int volumeBarYLocation;
    int volumeBarNumber;
    int i;
    int colorGreen;
    int volumeBarHeightIncrement;
    int volumeBarXLocationIncrement;
    int volumeBarYLocationIncrement;
    int greenGradientIncrement;

    volumeBarNumber = 20; 
    volumeBarHeight = 4;
    volumeBarHeightIncrement = 2;
    volumeBarXLocation = 880;
    volumeBarXLocationIncrement = 6;
    volumeBarYLocation = 50;
    volumeBarYLocationIncrement = 2;
    greenGradientIncrement = 8;


    for (i = 0; i < volumeBarNumber; i++)
    {
        volumeBackgroundSurface = SDL_CreateRGBSurface(0,4, volumeBarHeight,32,0,0,0,0);
        SDL_FillRect(volumeBackgroundSurface, NULL, SDL_MapRGB(volumeBackgroundSurface->format,0,0,0));
        SDL_Rect volumeBarLocation = {volumeBarXLocation,volumeBarYLocation,0,0};
        SDL_BlitSurface(volumeBackgroundSurface, NULL, surface, &volumeBarLocation);
        SDL_FreeSurface(volumeBackgroundSurface);

        //Increments for changing bar size
        volumeBarHeight += volumeBarHeightIncrement;
        volumeBarXLocation += volumeBarXLocationIncrement; 
        volumeBarYLocation -= volumeBarYLocationIncrement;
    }

    // Volume bar
    SDL_Surface *volumeSurface;
    
    volumeBarHeight = 4;
    volumeBarXLocation = 880;
    volumeBarYLocation = 50;
    colorGreen = 162;
    songVolumePercent = songVolumePercent * volumeBarNumber - 0.1;

    for (i = 0; i < songVolumePercent; i++) 
    {
        volumeSurface = SDL_CreateRGBSurface(0,4, volumeBarHeight, 32,0,0,0,0); 
        SDL_FillRect(volumeSurface, NULL, SDL_MapRGB(volumeSurface->format,255,colorGreen,0)); 
        SDL_Rect volumeBarLocation = {volumeBarXLocation, volumeBarYLocation, 0, 0}; 
        SDL_BlitSurface(volumeSurface, NULL, surface, &volumeBarLocation);
        SDL_FreeSurface(volumeSurface);
    
        // Increments for changing bar size and gradient
        volumeBarHeight += volumeBarHeightIncrement; 
        colorGreen -= greenGradientIncrement; 
        volumeBarXLocation += volumeBarXLocationIncrement; 
        volumeBarYLocation -= volumeBarYLocationIncrement; 
    }
}

void MusicBar::update()
{
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format,43,43,43)); 
   
    drawSongName();
    drawSongTime();
    drawVolumeBar();
}

SDL_Surface* MusicBar::returnMusicBar()
{
    return surface;
}
#endif













