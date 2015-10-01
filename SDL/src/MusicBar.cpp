#include "MusicBar.h"

MusicBar::MusicBar(SongPlayer *songPlayer)
{
    mPlayer = songPlayer;
    int musicBarSurfaceWidth = 1080;
    int musicBarSurfaceHeight = 32;
    surface = SDL_CreateRGBSurface(0, musicBarSurfaceWidth, musicBarSurfaceHeight, 32, 0, 0, 0, 0);
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format,255,0,0));
    init();    
}

int MusicBar::init()
{
    // Initalize SDL_ttf Library
    if (TTF_Init() !=0)
    {
        std::cerr << "TTF_Init Failed" << TTF_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    // Loads a Font
    font = TTF_OpenFont("src/FreeSans.ttf", 12);
    if (font == NULL)
    {
        std::cerr << "TTF_OpenFont Failed" << TTF_GetError << std::endl;
        TTF_Quit();
        SDL_Quit();
        exit(1);
    }
}

void MusicBar::drawSongName()
{
   
    // Gets current song and converts to char
    std::string songName = mPlayer->currentSong();
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

    //double songTime = 8;
    int songLength = mPlayer->getSongLength();
    double songTime = mPlayer->getCurrentTime();
    int minutes;
    int seconds;
    
    printf("The song length is %d \n", songLength);
    //double songTime = getSongLength();
    
    minutes = songLength / 60;
    seconds = songLength % 60;

    std::string sMinutes;
    std::stringstream convert1;
    convert1 << minutes;
    sMinutes = convert1.str();

    std::string sSeconds;
    std::stringstream convert2;
    convert2 << seconds;
    sSeconds = convert2.str();

    std::string sLength;
    sLength = sMinutes + ":" + sSeconds;
    const char *xLength = sLength.c_str();
    printf("Song Length in string: %s\n", xLength);

    printf("minutes: %d, seconds %d\n", minutes, seconds);
    printf("The time is %lf \n", songTime);
    
    std::string sTime;
    std::stringstream convert;
    convert << songTime;
    sTime = convert.str();
    const char * xtime = sTime.c_str();


    // Write text to surface
    SDL_Surface *time;
    SDL_Surface *length;
    SDL_Color text_color = {255, 255, 255};
    //SDL_Color text_color2 = {0, 0, 0};

    //text = TTF_RenderText_Shaded(font, "Text", text_color, text_color2);
    time = TTF_RenderText_Solid(font, xtime, text_color); 
    length = TTF_RenderText_Solid(font, xLength, text_color);
    //length = TTF_RenderText_Solid(font, 
    SDL_Rect textLocation = {25, 0, 0, 0};

    // Apply the text to surface
    SDL_BlitSurface(time, NULL, surface, NULL );
    SDL_BlitSurface(length, NULL, surface, &textLocation);
    
    printf("Time is: %s\n",sTime.c_str());
}

void MusicBar::drawVolumeBar()
{
    double songVolume = mPlayer->getVolume();
    printf("Song volume is: %lf\n", songVolume);

    double maxVolume = 2.0;
    double songVolumePercent;
    songVolumePercent = songVolume / maxVolume * 100;
}


void MusicBar::update()
{
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format,255,0,0));
    drawSongName();
    drawTime();
    drawVolumeBar();
}

SDL_Surface* MusicBar::returnMusicBar()
{
    return surface;
}














