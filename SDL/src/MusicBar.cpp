#include "MusicBar.h"
#include <SDL_ttf.h>
#include <iostream>
#include <sstream>

MusicBar::MusicBar()
{
    int musicBarSurfaceWidth = 1080;
    int musicBarSurfaceHeight = 32;
    surface = SDL_CreateRGBSurface(0, musicBarSurfaceWidth, musicBarSurfaceHeight, 32, 0, 0, 0, 0);
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format,255,0,0));
 
    drawSongName();
    drawTime();
    
}

void MusicBar::drawSongName()
{
    // Initalize SDL_ttf Library
    if (TTF_Init() !=0)
    {
        std::cerr << "TTF_Init Failed" << TTF_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    // Loads a Font
    TTF_Font *font;
    font = TTF_OpenFont("/home/gordon/Documents/SolarCar/Schulich-Delta-OnBoard-Media-Control/SDL/src/FreeSans.ttf", 12);
    if (font == NULL)
    {
        std::cerr << "TTF_OpenFont Failed" << TTF_GetError << std::endl;
        TTF_Quit();
        SDL_Quit();
        exit(1);
    }
   
    // Gets current song and converts to char
    std::string songName = currentSong();
    // std::size_t pos = str.find(".mp3")
    int stringLength = songName.length();
    //std::cout << stringLength;
    std::string newString = songName.substr(12, stringLength - 16); 
    const char * song = newString.c_str();

    // Write text to surface
    SDL_Surface *text;
    SDL_Color text_color = {255, 255, 255};
    //SDL_Color text_color2 = {0, 0, 0};
    
    //text = TTF_RenderText_Shaded(font, "Text", text_color, text_color2);
    text = TTF_RenderText_Solid(font, song, text_color);

    int w,h;
    TTF_SizeText(font, song, &w, &h);
    //printf("width: %d, height %d\n", w, h);
    SDL_Rect textLocation = {1080/2 - w/2, 0, 0, 0};
    
    // Apply the text to surface
    SDL_BlitSurface(text, NULL, surface, &textLocation );
    
        
    printf("Song name is: %s\n",songName.c_str());
    printf("Song name is: %s\n",newString.c_str());
}

void MusicBar::drawTime()
{
    // Initalize SDL_ttf Library
    if (TTF_Init() !=0)
    {
        std::cerr << "TTF_Init Failed" << TTF_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    // Loads a Font
    TTF_Font *font;
    font = TTF_OpenFont("/home/gordon/Documents/SolarCar/Schulich-Delta-OnBoard-Media-Control/SDL/src/FreeSans.ttf", 12);
    if (font == NULL)
    {
        std::cerr << "TTF_OpenFont Failed" << TTF_GetError << std::endl;
        TTF_Quit();
        SDL_Quit();
        exit(1);
    }

//double songTime = 8;
double songTime = getCurrentTime();
//double songTime = getSongLength();
printf("The time is %lf \n", songTime);
std::string sTime;
std::stringstream convert;
convert << songTime;
sTime = convert.str();
const char * xtime = sTime.c_str();


    // Write text to surface
    SDL_Surface *time;
    SDL_Color text_color = {255, 255, 255};
    //SDL_Color text_color2 = {0, 0, 0};
    
    //text = TTF_RenderText_Shaded(font, "Text", text_color, text_color2);
    time = TTF_RenderText_Solid(font, xtime, text_color);
    
    SDL_RenderDrawLine
    //SDL_Rect textLocation = {0, 25, 0, 0};
    
    // Apply the text to surface
    SDL_BlitSurface(time, NULL, surface, NULL );


   printf("Time is: %s\n",sTime.c_str());
}

MusicBar::drawVolumeBar()
{
    // Initalize SDL_ttf Library
    if (TTF_Init() !=0)
    {
        std::cerr << "TTF_Init Failed" << TTF_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    // Loads a Font
    TTF_Font *font;
    font = TTF_OpenFont("/home/gordon/Documents/SolarCar/Schulich-Delta-OnBoard-Media-Control/SDL/src/FreeSans.ttf", 12);
    if (font == NULL)
    {
        std::cerr << "TTF_OpenFont Failed" << TTF_GetError << std::endl;
        TTF_Quit();
        SDL_Quit();
        exit(1);
    }
}

//MusicBar::Update()

SDL_Surface* MusicBar::returnMusicBar()
{
    return surface;
}














