#include "MusicBar.h"



//std::string songName;

MusicBar::MusicBar()
{ 
    std::string songName = currentSong();
    printf("Song name is: %s\n",songName.c_str());
    surface = SDL_CreateRGBSurface(0, 240, 240, 32, 0, 0, 0, 0);
    
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format,255,0,0));
}
//void MusicBar::drawSongName()
//{ 
    //TTF_FONT* font = TTF_OpenFont("monospace.ttf", size); 
    //SDL_Color foregroundColor = { 0, 0, 0 };
    //SDL_Color backgroundColor = { 255, 255, 255 };

    //SDL_Surface* textSurface = TTF_RenderText_Shaded(font, songName, foregroundColor, backgroundColor);
    //SDL_Rect textLocation = {0, 0, 10 , 10};
    //SDL_BlitSurface(textSurface, NULL, musicBar, &textLocation);
    //SDL_FreeSurface(textSurface);
    //TTF_CloseFont(font);
//}
// void MusicBar::MusicBar()
//
SDL_Surface* MusicBar::returnMusicBar()
{
    return surface;
}














