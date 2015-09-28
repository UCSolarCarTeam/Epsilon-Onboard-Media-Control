
#include <cv.h>
#include "opencv2/opencv.hpp"
#include "SongLoader.h"
#include "SongPlayer.h"
#include "videoStream.hpp"

//for the rasperry pi
#ifndef INT64_C
#define INT64_C(c) (c ## LL)
#define UINT64_C(c) (c ## ULL)
#endif
extern "C" {
    #include <SDL.h>
//    #include <SDL_thread.h>
    #include <SDL_ttf.h>
}
#include <iostream>
#include <stdio.h>
#include <unistd.h>

#ifdef __amd64__
    #ifndef RUNNINGONINTEL
    #define RUNNINGONINTEL
    #endif
#else
    #ifndef RUNNINGONPI
    #define RUNNINGONPI
    #endif
    #include <wiringPi.h>
#endif

using namespace cv;

#define SCREEN_HEIGHT 768
#define SCREEN_WIDTH 1232

void processEvents();
void signalToQuit();
void close();

bool updatedImage = false;
int bufferNumber = 1;

SDL_Renderer* renderer = NULL;
SDL_Window* window = NULL;

SDL_Rect videoRect;
int cameraHeight;
int cameraWidth;
int noSongs;

SongPlayer musicPlayer;
VideoStream backupCamera;

int quit;
/***********************************************************************
/*                          SDL functions
/***********************************************************************/
// Initializes SDL window / renderer for use

bool init_SDL()
{
    bool success = true;

    if (SDL_Init(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        window = SDL_CreateWindow("Video Application", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (renderer == NULL)
            {
                printf("Renderer could not be created. SDL_Error: %s \n", SDL_GetError());
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            }
        }
    }
    return success;
}

bool init_CameraSettings()
{
    int w, h;
    bool success = true;
    SDL_GetWindowSize(window, &w, &h);
    videoRect.x = 0;
    videoRect.y = 0;
    videoRect.w = w;
    videoRect.h = h-50; //change 50 to whatever height we want for the PI cam

    return success;
}


// Shows an individual frame of the supplied video
int show_Camera()
{
    if(backupCamera.imageReady())
    {
        IplImage* img = NULL;
        img = backupCamera.getFrame();
        SDL_Surface* surface = SDL_CreateRGBSurfaceFrom((void*)img->imageData,
            img->width,
            img->height,
            img->depth * img->nChannels,
            img->widthStep,
            0xff0000, 0x00ff00, 0x0000ff, 0
            );

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        surface = NULL;
        SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
        SDL_RenderCopyEx(renderer, texture, NULL, &videoRect ,0, NULL, flip);
        SDL_DestroyTexture(texture);
        return 1;
    }

    return 0;
}

void processEvents()
{
    SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    printf("SDL_QUIT was called\n");
                    signalToQuit();
                    close();
                    break;

                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            printf("Esc was Pressed!\n");
                            signalToQuit();
                            close();
                            break;
                        case SDLK_LEFT:
                            printf("Left arrow was Pressed!\n");
                            musicPlayer.previousSong();
                            break;
                        case SDLK_RIGHT:
                            printf("Right arrow was Pressed!\n");
                            musicPlayer.nextSong();
                            break;
                        case SDLK_UP:
                            musicPlayer.changeVolume(0.1);
                            break;
                        case SDLK_DOWN:
                            musicPlayer.changeVolume(-0.1);
                            break;
                        case SDLK_SPACE:
                            printf("Space was pressed!\n");
                            musicPlayer.playPause();
                    }
            }
        }
}


/* Signals all the threads to quit and then waits for the threads */
void signalToQuit()
{
    backupCamera.signalToQuit();
    musicPlayer.songQuit();
}

/* Cleans up and should free everything used in the program*/
void close()
{
    musicPlayer.closeSongPlayer();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;
    SDL_Quit();
    exit(0);
}

int main(int argc, char* argv[])
{
    if (!init_SDL())
    {
        fprintf(stderr, "Could not initialize SDL!\n");
        return -1;
    }
    if (!init_CameraSettings())
    {
        printf("Failed to load settings!\n");
        return -1;
    }

    if (musicPlayer.initSongPlayer())
    {
        fprintf(stderr, "No SongLibrary Folder! Not creating Music Thread!\n");
    }
    else 
    {
        musicPlayer.StartInternalThread();
    }
    backupCamera.StartInternalThread();

    while (!quit)
    {
        processEvents();
        if (show_Camera())
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderPresent(renderer);
            SDL_RenderClear(renderer);
        }
    }

    musicPlayer.WaitForInternalThreadToExit();
    backupCamera.WaitForInternalThreadToExit();
    return 0;
}
