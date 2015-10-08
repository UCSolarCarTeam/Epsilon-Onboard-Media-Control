#include "MusicBar.h"

MusicBar::MusicBar(SongPlayer *songPlayer)
{
    mPlayer = songPlayer;
    int musicbarSurfaceWidth = 1080;
    int musicbarSurfaceHeight = 64;
    surface = SDL_CreateRGBSurface(0, musicbarSurfaceWidth, musicbarSurfaceHeight, 32, 0, 0, 0, 0);
    init();    
}

int MusicBar::init()
{
    int songNameFontSize; 
    int timeFontSize;
    
    songNameFontSize = 50;
    timeFontSize = 20;
    
    if (TTF_Init() !=0)
    {
        fprintf(stderr, "TTF_Init Failed%s\n", TTF_GetError());
        SDL_Quit();
        exit(1);
    }

    songNameFont = TTF_OpenFont("assets/Trebuchet-MS.ttf", songNameFontSize);
    if (songNameFont == NULL)
    {
        fprintf(stderr, "TTF_OpenFont Failed%s\n", TTF_GetError());
        TTF_Quit();
        SDL_Quit();
        exit(1);
    }
    
    timeFont = TTF_OpenFont("assets/Trebuchet-MS.ttf", timeFontSize);
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
    songName = songName.substr(12, songStringLength - 16); // COMMENT ON WHAT 12 and 16 ARE
    songChar = songName.c_str();
    
    SDL_Surface *songSurface;
    SDL_Color songColor = {255, 255, 255};
    songSurface = TTF_RenderText_Solid(songNameFont, songChar, songColor);
    TTF_SizeText(songNameFont, songChar, &songWidth, &songHeight);
    SDL_Rect songLocation = {1080/2 - songWidth/2, 0, 0, 0};
    SDL_BlitSurface(songSurface, NULL, surface, &songLocation);
    SDL_FreeSurface(songSurface);
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
    
    std::stringstream convert_songCurrentMins;
    std::stringstream convert_songCurrentSecs;
    convert_songCurrentMins << songCurrentMins;
    convert_songCurrentSecs << songCurrentSecs;
    songCurrentStrMins =  convert_songCurrentMins.str();
    songCurrentStrSecs = convert_songCurrentSecs.str();
    
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

    std::stringstream convertSongTotalMins;
    std::stringstream convertSongTotalSecs;
    convertSongTotalMins << songTotalMins;
    convertSongTotalSecs << songTotalSecs;
    songTotalStrMins = convertSongTotalMins.str();
    songTotalStrSecs = convertSongTotalSecs.str();

    if (songTotalSecs < 10)
    {
        songTotalStrTime = songTotalStrMins + ":0" + songTotalStrSecs;
    }
    else
    {
        songTotalStrTime = songTotalStrMins + ":" + songTotalStrSecs;
    }

    songTotalCharTime =  songTotalStrTime.c_str();
    
    SDL_Surface *songCurrentTimeSurface;
    SDL_Color songCurrentTimeColor = {255, 255, 255};
    songCurrentTimeSurface = TTF_RenderText_Solid(timeFont, songCurrentCharTime, 
                                                     songCurrentTimeColor);
    SDL_Rect songCurrentTimeLocation = {0, 4, 0, 0};
    SDL_BlitSurface(songCurrentTimeSurface, NULL, surface, &songCurrentTimeLocation);
    SDL_FreeSurface(songCurrentTimeSurface);
    
    SDL_Surface *songTotalTimeSurface;
    SDL_Color songTotalTimeColor = {255, 255, 255};
    songTotalTimeSurface = TTF_RenderText_Solid(timeFont, songTotalCharTime,
                                                   songTotalTimeColor);
    TTF_SizeText(timeFont, songTotalCharTime, &totalTimeWidth, &totalTimeHeight);
    SDL_Rect songTotalTimeLocation = {1080 - totalTimeWidth, 4, 0};
    SDL_BlitSurface(songTotalTimeSurface, NULL, surface, &songTotalTimeLocation);
    SDL_FreeSurface(songTotalTimeSurface);

    SDL_Surface *songTimebarSurface;
    songTimebarSurface = SDL_CreateRGBSurface(0, 0 + songCurrentPercent*1080, 3, 32, 0, 0, 0, 0);
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
    songVolumeMax = 2.0;

    songVolumeCurrent = mPlayer->getVolume();
    
    songVolumePercent = songVolumeCurrent / songVolumeMax;

    //SDL_Surface *volumeBackgroundSurface;
    //volumeBackgroundSurface = SDL_CreateRGBSurface(0,200,4,32,0,0,0,0);
    //SDL_FillRect(volumeBackgroundSurface, NULL, SDL_MapRGB(volumeBackgroundSurface->format,0,0,0));
    //SDL_Rect volumeBackgroundLocation = {878, 58,0,0};
    //SDL_BlitSurface(volumeBackgroundSurface, NULL, surface, &volumeBackgroundLocation);
    //SDL_FreeSurface(volumeBackgroundSurface);
    
    //SDL_Surface *volumeSurface;
    //volumeSurface = SDL_CreateRGBSurface(0,0 + songVolumePercent*200, 4, 32,0,0,0,0);
    //SDL_FillRect(volumeSurface, NULL, SDL_MapRGB(volumeSurface->format,0,162,255));
    //SDL_Rect volumeLocation = {878, 58, 0, 0};
    //SDL_BlitSurface(volumeSurface, NULL, surface, &volumeLocation);
    //SDL_FreeSurface(volumeSurface);

    // Volume Background Bar Prototype
    SDL_Surface *volumeBackgroundSurface;
    int volumeBarHeight;
    volumeBarHeight = 4;
    int volumeBarBackground_x_Location;
    int volumeBarBackground_y_Location;
    volumeBarBackground_x_Location = 895;
    volumeBarBackground_y_Location = 58;
    int i;
    
    for (i = 0; i < 24; i++)
    {
        volumeBackgroundSurface = SDL_CreateRGBSurface(0,4,volumeBarHeight,32,0,0,0,0);
        volumeBarHeight += 2;
        SDL_FillRect(volumeBackgroundSurface, NULL, SDL_MapRGB(volumeBackgroundSurface->format,0,0,0));
        SDL_Rect volumeBackgroundLocation = {volumeBarBackground_x_Location,volumeBarBackground_y_Location,0,0};
        volumeBarBackground_x_Location += 6;
        volumeBarBackground_y_Location -= 2;
        SDL_BlitSurface(volumeBackgroundSurface, NULL, surface, &volumeBackgroundLocation);
        SDL_FreeSurface(volumeBackgroundSurface);
    }

    // Volume Bar Prototype
    SDL_Surface *volumeSurface;
    int volumeBar_x_Location;
    int volumeBar_y_Location;
    int volumeBar_Height2;
    int color_gradient;
    volumeBar_Height2 = 4;
    volumeBar_x_Location = 895;
    volumeBar_y_Location = 58;
    songVolumePercent = songVolumePercent * 24 - 0.1;
    int green_color_gradient = 162;
    
    for (i = 0; i < songVolumePercent; i++) 
    {
        volumeSurface = SDL_CreateRGBSurface(0,4, volumeBar_Height2, 32,0,0,0,0);
        volumeBar_Height2 += 2;
        SDL_FillRect(volumeSurface, NULL, SDL_MapRGB(volumeSurface->format,255,green_color_gradient,0));
        SDL_Rect volumeLocation = {volumeBar_x_Location, volumeBar_y_Location, 0, 0};
        green_color_gradient -= 6;
        volumeBar_x_Location += 6;
        volumeBar_y_Location -= 2;
        SDL_BlitSurface(volumeSurface, NULL, surface, &volumeLocation);
        SDL_FreeSurface(volumeSurface);
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














