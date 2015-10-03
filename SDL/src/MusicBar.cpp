#include "MusicBar.h"

MusicBar::MusicBar(SongPlayer *songPlayer)
{
    mPlayer = songPlayer;
    int musicBarSurfaceWidth = 1080;
    int musicBarSurfaceHeight = 64;
    surface = SDL_CreateRGBSurface(0, musicBarSurfaceWidth, musicBarSurfaceHeight, 32, 0, 0, 0, 0);
    init();    
}

int MusicBar::init()
{
    // Initalize SDL_TTF Library
    if (TTF_Init() !=0)
    {
        std::cerr << "TTF_Init Failed" << TTF_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    // Loads font for song name 
    font_one = TTF_OpenFont("assets/Trebuchet-MS.ttf", 50);
    if (font_one == NULL)
    {
        std::cerr << "TTF_OpenFont Failed" << TTF_GetError << std::endl;
        TTF_Quit();
        SDL_Quit();
        exit(1);
    }
    
    // Loads font for time
    font_two = TTF_OpenFont("assets/Trebuchet-MS.ttf", 20);
    if (font_two == NULL)
    {
        std::cerr << "TTF_OpenFont Failed" << TTF_GetError << std::endl;
        TTF_Quit();
        SDL_Quit();
        exit(1);
    }
}

void MusicBar::drawSongName()
{
    std::string song_name;
    int song_string_length;
    const char * song_char;
    int song_width;
    int song_height;

    
    // Get song name and convert to char
    song_name = mPlayer->currentSong();
    song_string_length = song_name.length();
    song_name = song_name.substr(12, song_string_length - 16);
    song_char = song_name.c_str();
    
   // std::string songName = mPlayer->currentSong();
    //int stringLength = songName.length();
    //std::cout << stringLength;
    //std::string song_name = songName.substr(12, stringLength - 16); 
    //const char * song = newString.c_str();

    
    // Creates song name song surface
    SDL_Surface *song_surface;
    SDL_Color song_color = {255, 255, 255};
    song_surface = TTF_RenderText_Solid(font_one, song_char, song_color);
    TTF_SizeText(font_one, song_char, &song_width, &song_height);
    SDL_Rect song_location = {1080/2 - song_width/2, 0, 0, 0};
    SDL_BlitSurface(song_surface, NULL, surface, &song_location);
    SDL_FreeSurface(song_surface);

    
    // Write text to surface
    //SDL_Surface *text;
    //SDL_Color text_color = {255, 255, 255};
    //SDL_Color text_color2 = {0, 0, 0};t
    
    //text = TTF_RenderText_Shaded(font, "Text", text_color, text_color2);
    //text = TTF_RenderText_Solid(font_one, song_char, text_color);

    //int w,h;
    //TTF_SizeText(font_one, song_char, &w, &h);
    //printf("width: %d, height %d\n", w, h);
    //SDL_Rect textLocation = {1080/2 - w/2, 0, 0, 0};
    
    // Apply the text to surface
    //SDL_BlitSurface(text, NULL, surface, &textLocation );
    
        
    //printf("Song name is: %s\n",song_name.c_str());
    //printf("Song name is: %s\n",newString.c_str());
}

void MusicBar::drawSongTime()
{
    // Constants for current song time
    double song_current_time;
    int song_current_mins;
    int song_current_secs;
    double song_current_percent;
    int song_current_int_time;
 
    std::string song_current_str_time;
    std::string song_current_str_mins;
    std::string song_current_str_secs;
    const char * song_current_char_time; 

    // Constants for total song time 
    double song_total_time;
    int song_total_mins;
    int song_total_secs;
    int song_total_int_time;

    std::string song_total_str_time;
    std::string song_total_str_mins;
    std::string song_total_str_secs;
    const char * song_total_char_time;

    int total_time_width;
    int total_time_height;


    //double songTime = 8;
    //int songLength = mPlayer->getSongLength();
    //double songTime = mPlayer->getCurrentTime();
    //int minutes;
    //int seconds;
    //double songtimePercent;
    //int currentmins;
    //int currentsecs;
    
    // Gets current song time and total song time
    song_current_time = mPlayer->getCurrentTime();
    song_total_time = mPlayer->getSongLength();
    
    // Conversions for current song time to minutes and seconds 
    song_current_percent = song_current_time / song_total_time; 
    //printf("Song percent is: %lf \n", song_current_percent);
    song_current_int_time = song_current_time;
    song_current_mins = song_current_int_time / 60;
    song_current_secs = song_current_int_time % 60;

    // Conversion for total song time to minute and seconds
    song_total_time = song_total_time - song_current_time; // Remove to stop end time increment
    song_total_int_time = song_total_time;
    //printf("song ends in: %lf", song_total_time);
    song_total_mins = song_total_time / 60;
    song_total_secs = song_total_int_time % 60;
    
    
    //songtimePercent = songTime / songLength ;

    //printf("Song Percent is: %lf\n", songtimePercent);

    //printf("The song length is %d \n", songLength);
    //double songTime = getSongLength();
    
    //int integersongTime;
    //integersongTime = songTime ;
    //currentmins = integersongTime / 60;
    //currentsecs = integersongTime % 60;
    
    // Conversions for current song time to strings then to final char
    std::stringstream convert_song_current_mins;
    std::stringstream convert_song_current_secs;
    convert_song_current_mins << song_current_mins;
    convert_song_current_secs << song_current_secs;
    song_current_str_mins =  convert_song_current_mins.str();
    song_current_str_secs = convert_song_current_secs.str();
    
    if (song_current_secs < 10)
    {
        song_current_str_time = song_current_str_mins + ":0" + 
                                song_current_str_secs;
    }
    else
    {
        song_current_str_time = song_current_str_mins + ":" + song_current_str_secs;
    }
    
    song_current_char_time = song_current_str_time.c_str();

   

    //minutes = songLength / 60;
    //seconds = songLength % 60;

    // Conversions for total song time to strings then to final char
    std::stringstream convert_song_total_mins;
    std::stringstream convert_song_total_secs;
    convert_song_total_mins << song_total_mins;
    convert_song_total_secs << song_total_secs;
    song_total_str_mins = convert_song_total_mins.str();
    song_total_str_secs = convert_song_total_secs.str();

    if (song_total_secs < 10)
    {
        song_total_str_time = song_total_str_mins + ":0" + song_total_str_secs;
    }
    else
    {
        song_total_str_time = song_total_str_mins + ":" + song_total_str_secs;
    }

    song_total_char_time =  song_total_str_time.c_str();
    
    //printf("Song Length in string: %s\n", xLength);
    //printf("minutes: %d, seconds %d\n", minutes, seconds);
    //printf("The time is %d \n", songTime);
    //std::string sTime;
    //std::stringstream convert;
    //convert << songTime;
    //sTime = convert.str();
    //const char * xtime = sTime.c_str();

    // Creates current song time surface
    SDL_Surface *song_current_time_surface;
    SDL_Color song_current_time_color = {255, 255, 255};
    song_current_time_surface = TTF_RenderText_Solid(font_two, song_current_char_time, 
                                                     song_current_time_color);
    SDL_Rect song_current_time_location = {0, 4, 0, 0};
    SDL_BlitSurface(song_current_time_surface, NULL, surface, &song_current_time_location);
    SDL_FreeSurface(song_current_time_surface);
    
    // Creates total song time surface
    SDL_Surface *song_total_time_surface;
    SDL_Color song_total_time_color = {255, 255, 255};
    song_total_time_surface = TTF_RenderText_Solid(font_two, song_total_char_time,
                                                   song_total_time_color);
    TTF_SizeText(font_two, song_total_char_time, &total_time_width, &total_time_height);
    SDL_Rect song_total_time_location = {1080 - total_time_width, 4, 0};
    SDL_BlitSurface(song_total_time_surface, NULL, surface, &song_total_time_location);
    SDL_FreeSurface(song_total_time_surface);

    // Write text to surface
    //SDL_Surface *time;
    //SDL_Surface *length;
    //SDL_Color text_color = {255, 255, 255};
    //SDL_Color text_color2 = {0, 0, 0};

    //text = TTF_RenderText_Shaded(font, "Text", text_color, text_color2);
    //time = TTF_RenderText_Solid(font_two, song_current_char_time, text_color); 
    //length = TTF_RenderText_Solid(font_two, xLength, text_color);
    //length = TTF_RenderText_Solid(font, 

    //int lengthWidth, lengthHeight;
    //TTF_SizeText(font_two, xLength, &lengthWidth, &lengthHeight);
    
    //SDL_Rect timeLocation = {0, 4, 0, 0};
    //SDL_Rect lengthLocation = {1080-lengthWidth, 4, 0};
    // Apply the text to surface
    //SDL_BlitSurface(time, NULL, surface, &timeLocation );
    //SDL_BlitSurface(length, NULL, surface, &lengthLocation);
    
    //printf("Time is: %s\n",sCurrentTime.c_str());


    //SDL_Surface *tBar;

    //tBar = SDL_CreateRGBSurface(0, 1080, 1, 32, 0, 0, 0, 0);
    //SDL_FillRect(tBar, NULL, SDL_MapRGB(tBar->format,255,255,255));
    
    //SDL_Rect tLocation = {0,0,0,0};

    //SDL_BlitSurface(tBar, NULL, surface, &tLocation);
    
    // Creates song time bar surface
    SDL_Surface *song_timebar_surface;
    song_timebar_surface = SDL_CreateRGBSurface(0, 0 + song_current_percent*1080, 2, 32, 0, 0, 0, 0);
    SDL_FillRect(song_timebar_surface, NULL, SDL_MapRGB(song_timebar_surface->format,0,162,255));
    SDL_Rect song_timebar_location = {0, 0, 0, 0};
    SDL_BlitSurface(song_timebar_surface, NULL, surface, &song_timebar_location);
    SDL_FreeSurface(song_timebar_surface);
}

void MusicBar::drawVolumeBar()
{
    double songVolume = mPlayer->getVolume();
    //printf("Song volume is: %lf\n", songVolume);

    double maxVolume = 2.0;
    double songVolumePercent;
    songVolumePercent = songVolume / maxVolume;

    SDL_Surface *volBackBar;
    volBackBar = SDL_CreateRGBSurface(0, 200, 4, 32, 0, 0, 0, 0);
    SDL_FillRect(volBackBar, NULL, SDL_MapRGB(volBackBar->format,0,0,0));
    SDL_Rect vbLocation = {440, 58, 0, 0};
    SDL_BlitSurface(volBackBar, NULL, surface, &vbLocation);
    SDL_FreeSurface(volBackBar);
    
    SDL_Surface *volBar;
    volBar = SDL_CreateRGBSurface(0,0 + songVolumePercent*200, 4, 32, 0, 0, 0 ,0);
    // UNCOMMENT TO CHANGE COLOUR SCHEME
    SDL_FillRect(volBar, NULL, SDL_MapRGB(volBar->format,0,162,255));
    
    //SDL_FillRect(volBar, NULL, SDL_MapRGB(volBar->format,255,255,255));
    SDL_Rect vLocation = {440, 58, 0, 0};
    SDL_BlitSurface(volBar, NULL, surface, &vLocation);
    SDL_FreeSurface(volBar);
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














