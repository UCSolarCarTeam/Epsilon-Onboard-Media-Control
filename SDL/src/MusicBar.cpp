#include "MusicBar.h"



//std::string songName;

MusicBar::MusicBar()
{

std::string songName = currentSong();
printf("%s\n",songName.c_str());
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














