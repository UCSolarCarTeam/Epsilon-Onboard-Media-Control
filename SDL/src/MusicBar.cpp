#include "MusicBar.h"

MusicBar::MusicBar(SongPlayer *songPlayer)
{
    mPlayer = songPlayer;
    musicbarSurfaceWidth = 1080;
    musicbarSurfaceHeight = 64;
    xSongLocation = 150;
    getTimeInitialization = false;
    initialization = false;
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

    songNameFont = TTF_OpenFont("/usr/share/fonts/ArialUni.ttf", songNameFontSize);
    if (songNameFont == NULL)
    {
        fprintf(stderr, "TTF_OpenFont Failed%s\n", TTF_GetError());
        TTF_Quit();
        SDL_Quit();
        exit(1);
    }
    
    timeFont = TTF_OpenFont("/usr/share/fonts/ArialUni.ttf", timeFontSize);
    if (timeFont == NULL)
    {
        fprintf(stderr, "TTF_OpenFont Failed%s\n", TTF_GetError());
        TTF_Quit();
        SDL_Quit();
        exit(1);
    }
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
    
    // SDL CALLS // 
    
   // SDL_Surface *songSurface;
    //SDL_Color songColor = {255, 255, 255}; 
    //songSurface = TTF_RenderUTF8_Blended(songNameFont, songChar, songColor);
    //TTF_SizeText(songNameFont, songChar, &songWidth, &songHeight);
    //SDL_Rect songLocation = {(880-50)/2 - songWidth/2, musicbarSurfaceHeight/2 - songHeight/2, 0, 0}; //880 is start of volume bar, 50 is end of current time
    //SDL_BlitSurface(songSurface, NULL, surface, &songLocation);
    //SDL_FreeSurface(songSurface);

    // Song Scrolling Prototype
    
    double songCurrentTime;
    songCurrentTime = mPlayer->getCurrentTime();
    
    if (songCurrentTime >= 0 && songCurrentTime <= 3)
    {
        xSongLocation = 150;
        initialization = false;
    }

    if (xSongLocation > 800)
    {
        initialization = true;
        getTimeInitialization = false;
    }
   
    if (initialization == true)
    {  
        if (xSongLocation <= 150)
        {
            if (getTimeInitialization == false)
            {
                songTimeMark = songCurrentTime;
                getTimeInitialization = true;
            }   
            if (songCurrentTime < (songTimeMark + 3)) 
            {
                xSongLocation = 150;
            }       
        }
    }
    
    
    SDL_Surface *songSurface;

    SDL_Rect songLocation;

    SDL_Color songColor = {255, 255, 255}; 
    songSurface = TTF_RenderUTF8_Blended(songNameFont, songChar, songColor);
    TTF_SizeText(songNameFont, songChar, &songWidth, &songHeight);

    // SONG NAME BACKGROUND
    SDL_Surface *songOutline;
    songOutline = SDL_CreateRGBSurface(0, 700, 52, 32, 0, 0, 0, 0);
    SDL_FillRect(songOutline, NULL, SDL_MapRGB(songOutline->format,35,35,35));
    SDL_Rect songOutlineLocation = {150, 6, 0, 0};
    SDL_BlitSurface(songOutline, NULL, surface, &songOutlineLocation);
    SDL_FreeSurface(songOutline);
    // SONG NAME BACKGROUND

    if (songWidth >= 700)
    {    
        songLocation = {xSongLocation, musicbarSurfaceHeight/2 - songHeight/2, 0, 0}; 
        SDL_BlitSurface(songSurface, NULL, surface, &songLocation);
        SDL_FreeSurface(songSurface);
        xSongLocation = xSongLocation - 20;
        if (xSongLocation + songWidth < 150)
        {
            xSongLocation = 880;
        }
    } 
    else 
    {
        songLocation = {(500) - (songWidth/2), musicbarSurfaceHeight/2 - songHeight/2, 0, 0}; //880 is start of volume bar, 50 is end of current time
        SDL_BlitSurface(songSurface, NULL, surface, &songLocation);
        SDL_FreeSurface(songSurface);
    }
    
    SDL_Surface *Rect1Surface;
    Rect1Surface = SDL_CreateRGBSurface(0, 150, 64, 32, 0, 0, 0, 0);
    SDL_FillRect(Rect1Surface, NULL, SDL_MapRGB(Rect1Surface->format,43,43,43));
    SDL_Rect Rect1Location = {0,0,0,0};
    SDL_BlitSurface(Rect1Surface, NULL, surface, &Rect1Location);
    SDL_FreeSurface(Rect1Surface);

    SDL_Surface *Rect2Surface;
    Rect2Surface = SDL_CreateRGBSurface(0, 1080-850, 64, 32, 0, 0, 0, 0);
    SDL_FillRect(Rect2Surface, NULL, SDL_MapRGB(Rect2Surface->format,43,43,43));
    SDL_Rect Rect2Location = {850,0,0,0};
    SDL_BlitSurface(Rect2Surface, NULL, surface, &Rect2Location);
    SDL_FreeSurface(Rect2Surface);
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
    songTimebarSurface = SDL_CreateRGBSurface(0, 0 + songCurrentPercent*musicbarSurfaceWidth, 3, 32, 0, 0, 0, 0); 
    SDL_FillRect(songTimebarSurface, NULL, SDL_MapRGB(songTimebarSurface->format,0,162,255));
    SDL_Rect songTimebarLocation = {0, 0, 0, 0};
    SDL_BlitSurface(songTimebarSurface, NULL, surface, &songTimebarLocation);
    SDL_FreeSurface(songTimebarSurface);
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

    volumeBarNumber = 20; 
    volumeBarHeight = 4;
    volumeBarXLocation = 880;
    volumeBarYLocation = 50;
    
    for (i = 0; i < volumeBarNumber; i++)
    {
        volumeBackgroundSurface = SDL_CreateRGBSurface(0,4, volumeBarHeight,32,0,0,0,0);
        SDL_FillRect(volumeBackgroundSurface, NULL, SDL_MapRGB(volumeBackgroundSurface->format,0,0,0));
        SDL_Rect volumeBarLocation = {volumeBarXLocation,volumeBarYLocation,0,0};
        SDL_BlitSurface(volumeBackgroundSurface, NULL, surface, &volumeBarLocation);
        SDL_FreeSurface(volumeBackgroundSurface);

        //Increments for changing bar size
        volumeBarHeight += 2;
        volumeBarXLocation += 6; 
        volumeBarYLocation -= 2;
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
        volumeBarHeight += 2; 
        colorGreen -= 8; 
        volumeBarXLocation += 6; 
        volumeBarYLocation -= 2; 
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














