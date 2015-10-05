#include "MusicBar.h"

MusicBar::MusicBar(SongPlayer *songPlayer)
{
    mPlayer = songPlayer;
    int musicbar_surface_width = 1080;
    int musicbar_surface_height = 64;
    surface = SDL_CreateRGBSurface(0, musicbar_surface_width, musicbar_surface_height, 32, 0, 0, 0, 0);
    init();    
}

int MusicBar::init()
{
    if (TTF_Init() !=0)
    {
        fprintf(stderr, "TTF_Init Failed%s\n", TTF_GetError());
        SDL_Quit();
        exit(1);
    }

    song_name_font = TTF_OpenFont("assets/Trebuchet-MS.ttf", 50);
    if (song_name_font == NULL)
    {
        fprintf(stderr, "TTF_OpenFont Failed%s\n", TTF_GetError());
        TTF_Quit();
        SDL_Quit();
        exit(1);
    }
    
    time_font = TTF_OpenFont("assets/Trebuchet-MS.ttf", 20);
    if (time_font == NULL)
    {
        fprintf(stderr, "TTF_OpenFont Failed%s\n", TTF_GetError());
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

    song_name = mPlayer->currentSong();
    song_string_length = song_name.length();
    song_name = song_name.substr(12, song_string_length - 16);
    song_char = song_name.c_str();
    
    SDL_Surface *song_surface;
    SDL_Color song_color = {255, 255, 255};
    song_surface = TTF_RenderText_Solid(song_name_font, song_char, song_color);
    TTF_SizeText(song_name_font, song_char, &song_width, &song_height);
    SDL_Rect song_location = {1080/2 - song_width/2, 0, 0, 0};
    SDL_BlitSurface(song_surface, NULL, surface, &song_location);
    SDL_FreeSurface(song_surface);
}

void MusicBar::drawSongTime()
{ 
    double song_current_time;
    int song_current_mins;
    int song_current_secs;
    double song_current_percent;
    int song_current_int_time;
 
    std::string song_current_str_time;
    std::string song_current_str_mins;
    std::string song_current_str_secs;
    const char * song_current_char_time; 

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

    song_current_time = mPlayer->getCurrentTime();
    song_total_time = mPlayer->getSongLength();
    
    song_current_percent = song_current_time / song_total_time; 
    song_current_int_time = song_current_time;
    song_current_mins = song_current_int_time / 60;
    song_current_secs = song_current_int_time % 60;

    //song_total_time = song_total_time - song_current_time; // Remove to stop end time increment
    song_total_int_time = song_total_time;
    song_total_mins = song_total_time / 60;
    song_total_secs = song_total_int_time % 60;
    
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
    
    SDL_Surface *song_current_time_surface;
    SDL_Color song_current_time_color = {255, 255, 255};
    song_current_time_surface = TTF_RenderText_Solid(time_font, song_current_char_time, 
                                                     song_current_time_color);
    SDL_Rect song_current_time_location = {0, 4, 0, 0};
    SDL_BlitSurface(song_current_time_surface, NULL, surface, &song_current_time_location);
    SDL_FreeSurface(song_current_time_surface);
    
    SDL_Surface *song_total_time_surface;
    SDL_Color song_total_time_color = {255, 255, 255};
    song_total_time_surface = TTF_RenderText_Solid(time_font, song_total_char_time,
                                                   song_total_time_color);
    TTF_SizeText(time_font, song_total_char_time, &total_time_width, &total_time_height);
    SDL_Rect song_total_time_location = {1080 - total_time_width, 4, 0};
    SDL_BlitSurface(song_total_time_surface, NULL, surface, &song_total_time_location);
    SDL_FreeSurface(song_total_time_surface);

    SDL_Surface *song_timebar_surface;
    song_timebar_surface = SDL_CreateRGBSurface(0, 0 + song_current_percent*1080, 3, 32, 0, 0, 0, 0);
    SDL_FillRect(song_timebar_surface, NULL, SDL_MapRGB(song_timebar_surface->format,0,162,255));
    SDL_Rect song_timebar_location = {0, 0, 0, 0};
    SDL_BlitSurface(song_timebar_surface, NULL, surface, &song_timebar_location);
    SDL_FreeSurface(song_timebar_surface);
}

void MusicBar::drawVolumeBar()
{
    double song_volume_current;
    double song_volume_percent;
    double song_volume_max;
    song_volume_max = 2.0;

    song_volume_current = mPlayer->getVolume();
    
    song_volume_percent = song_volume_current / song_volume_max;

    SDL_Surface *volume_bg_surface;
    volume_bg_surface = SDL_CreateRGBSurface(0,200,4,32,0,0,0,0);
    SDL_FillRect(volume_bg_surface, NULL, SDL_MapRGB(volume_bg_surface->format,0,0,0));
    SDL_Rect volume_bg_location = {878, 58,0,0};
    SDL_BlitSurface(volume_bg_surface, NULL, surface, &volume_bg_location);
    SDL_FreeSurface(volume_bg_surface);
    
    SDL_Surface *volume_surface;
    volume_surface = SDL_CreateRGBSurface(0,0 + song_volume_percent*200, 4, 32,0,0,0,0);
    SDL_FillRect(volume_surface, NULL, SDL_MapRGB(volume_surface->format,0,162,255));
    SDL_Rect volume_location = {878, 58, 0, 0};
    SDL_BlitSurface(volume_surface, NULL, surface, &volume_location);
    SDL_FreeSurface(volume_surface);
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














