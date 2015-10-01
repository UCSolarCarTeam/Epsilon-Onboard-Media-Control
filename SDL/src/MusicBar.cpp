#include "MusicBar.h"

MusicBar::MusicBar(SongPlayer *songPlayer)
{
    mPlayer = songPlayer;
    int musicBarSurfaceWidth = 1080;
    int musicBarSurfaceHeight = 64;
    surface = SDL_CreateRGBSurface(0, musicBarSurfaceWidth, musicBarSurfaceHeight, 32, 0, 0, 0, 0);
    //SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format,56,56,56));
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

    // Loads font for Song Name
    font = TTF_OpenFont("assets/LiberationSerif-Regular.ttf", 50);
    if (font == NULL)
    {
        std::cerr << "TTF_OpenFont Failed" << TTF_GetError << std::endl;
        TTF_Quit();
        SDL_Quit();
        exit(1);
    }

    font_two = TTF_OpenFont("assets/LiberationSerif-Regular.ttf", 20);
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
    //SDL_Color text_color2 = {0, 0, 0};t
    
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
    double songtimePercent;
    int currentmins;
    int currentsecs;
    
    songtimePercent = songTime / songLength ;
    printf("Song Percent is: %lf\n", songtimePercent);

    printf("The song length is %d \n", songLength);
    //double songTime = getSongLength();
    
    int integersongTime;
    integersongTime = songTime ;
    currentmins = integersongTime / 60;
    currentsecs = integersongTime % 60;
    
    std::string sCurrentMins;
    std::string sCurrentSecs;
    std::string sCurrentTime;
    std::stringstream convert3;
    std::stringstream convert4;
    convert3 << currentmins;
    convert4 << currentsecs;
    sCurrentMins = convert3.str();
    sCurrentSecs = convert4.str();
    
    if (currentsecs < 10)
    {
        sCurrentTime = sCurrentMins + ":0" + sCurrentSecs;
    }
    else
    {
        sCurrentTime = sCurrentMins + ":" + sCurrentSecs;
    }
    const char *xCurrentTime = sCurrentTime.c_str();

   
    songLength = songLength - songTime;

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
    if (seconds < 10)
    {
        sLength = sMinutes + ":0" + sSeconds;
    }
    else
    {
        sLength = sMinutes + ":" + sSeconds;
    }

    const char *xLength = sLength.c_str();
    printf("Song Length in string: %s\n", xLength);

    printf("minutes: %d, seconds %d\n", minutes, seconds);
    printf("The time is %d \n", songTime);
    
    //std::string sTime;
    //std::stringstream convert;
    //convert << songTime;
    //sTime = convert.str();
    //const char * xtime = sTime.c_str();


    // Write text to surface
    SDL_Surface *time;
    SDL_Surface *length;
    SDL_Color text_color = {255, 255, 255};
    //SDL_Color text_color2 = {0, 0, 0};

    //text = TTF_RenderText_Shaded(font, "Text", text_color, text_color2);
    time = TTF_RenderText_Solid(font_two, xCurrentTime, text_color); 
    length = TTF_RenderText_Solid(font_two, xLength, text_color);
    //length = TTF_RenderText_Solid(font, 

    int lengthWidth, lengthHeight;
    TTF_SizeText(font_two, xLength, &lengthWidth, &lengthHeight);
    
    SDL_Rect timeLocation = {0, 4, 0, 0};
    SDL_Rect lengthLocation = {1080-lengthWidth, 4, 0};
    // Apply the text to surface
    SDL_BlitSurface(time, NULL, surface, &timeLocation );
    SDL_BlitSurface(length, NULL, surface, &lengthLocation);
    
    printf("Time is: %s\n",sCurrentTime.c_str());


    //SDL_Surface *tBar;

    //tBar = SDL_CreateRGBSurface(0, 1080, 1, 32, 0, 0, 0, 0);
    //SDL_FillRect(tBar, NULL, SDL_MapRGB(tBar->format,255,255,255));
    
    //SDL_Rect tLocation = {0,0,0,0};

    //SDL_BlitSurface(tBar, NULL, surface, &tLocation);
    
   
    SDL_Surface *tick;
    tick = SDL_CreateRGBSurface(0, 0 + songtimePercent*1080, 1, 32, 0, 0, 0, 0);
    SDL_FillRect(tick, NULL, SDL_MapRGB(tick->format,255,255,255));

    SDL_Rect tkLocation = {0, 0, 0, 0};

    SDL_BlitSurface(tick, NULL, surface, &tkLocation);
    
    

}

void MusicBar::drawVolumeBar()
{
    double songVolume = mPlayer->getVolume();
    printf("Song volume is: %lf\n", songVolume);

    double maxVolume = 2.0;
    double songVolumePercent;
    songVolumePercent = songVolume / maxVolume;

    SDL_Surface *volBar;
    volBar = SDL_CreateRGBSurface(0,0 + songVolumePercent*200, 1, 32, 0, 0, 0 ,0);
    SDL_FillRect(volBar, NULL, SDL_MapRGB(volBar->format,255,255,255));

    SDL_Rect vLocation = {440, 63, 0, 0};
    
    SDL_BlitSurface(volBar, NULL, surface, &vLocation);
}


void MusicBar::update()
{
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format,43,43,43));
    drawSongName();
    drawTime();
    drawVolumeBar();
}

SDL_Surface* MusicBar::returnMusicBar()
{
    return surface;
}














