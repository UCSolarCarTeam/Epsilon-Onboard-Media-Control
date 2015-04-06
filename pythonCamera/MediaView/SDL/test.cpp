#include <highgui.h>
#include <cv.h>
#include "opencv2/opencv.hpp"
extern "C" {
    #include <SDL.h>
    #include <SDL_thread.h>
    #include <SDL_image.h>
    #include "libavcodec/avcodec.h"
    #include "libavformat/avformat.h"
}
#include <iostream>
#include <stdio.h>
#include <unistd.h>
//#include <vector>
bool sick = true;
using namespace cv;

// Necessary definitions
/*
#define SDL_AUDIO_BUFFER_SIZE 1024
#define AVCODEC_MAX_AUDIO_FRAME_SIZE 192000*/
#define SCREEN_HEIGHT 720
#define SCREEN_WIDTH 1440
#define MAX_CAMERAS 3

void close();
int backupWorker(void* data);

int videoStream = -1;
int audioStream = -1;
int quit = 0;
bool surfaceFree1 = true;
bool surfaceFree2 = true;
int failures = 0;

//
SDL_mutex* threadLock1 = NULL;
SDL_cond* surfaceReady1 = NULL;
SDL_cond* imageReady1 = NULL;
SDL_Surface* threadSurface1 = NULL;
SDL_Texture* threadText1 = NULL;

IplImage* threadImage1 = 0;
//

SDL_Renderer* renderer = NULL;
SDL_Window* window = NULL;

SDL_Rect videoRect;

AVFormatContext* ctxArray[MAX_CAMERAS] = {NULL};    // context array for all cameras
IplImage* imageArray[MAX_CAMERAS];      // image array for all cameras

AVFormatContext* pFormatCtx = NULL;


AVFormatContext* pFormatCtx2 = NULL;

/***********************************************************************
/*                          SDL functions 
/***********************************************************************/
// Initializes SDL window / renderer for use
bool init_SDL()
{
    bool success = true;
    
    if (SDL_Init(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) < 0)
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else 
    {
        window = SDL_CreateWindow("Video Application", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("error");
            success = false;
        }
        else {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (renderer == NULL)
            {
                    printf("Renderer could not be created. SDL_Error: %s \n", SDL_GetError());
                    success = false;
            }
            else 
            {
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                int imgFlags = IMG_INIT_PNG;
                if (! (IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not init. SDL_image error: %s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }
    videoRect.x = 0;
    videoRect.y = 0;
    videoRect.w = 640;
    videoRect.h = 480;

    return success;
}


int main(int argc, char* argv[])
{
    
    av_register_all();
    
    if (!init_SDL())
    {
        fprintf(stderr, "Could not initialize SDL!\n");
        return -1;
    }
    

    VideoCapture cap(0);
    
    if (!cap.isOpened())
    {
        fprintf(stderr, "Failed to load file!\n");
        return -1;
    }

    while (!quit)
    {

        SDL_Event event;
        SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
            quit = 1;
            close();
            SDL_Quit();
            exit(0);
            break;

            default:
            break;
        }
        Mat frame;
        cap >> frame; // get a new frame
        IplImage ipl_frame = frame;
        IplImage* img = &ipl_frame;

        threadSurface1 = SDL_CreateRGBSurfaceFrom((void*)img->imageData,
            img->width,
            img->height,
            img->depth * img->nChannels,
            img->widthStep,
            0xff0000, 0x00ff00, 0x0000ff, 0
            );

        if( threadSurface1 == NULL )
        {
            printf( "Unable to create texture from! SDL Error: %s\n", SDL_GetError() );
        }


        threadText1 = SDL_CreateTextureFromSurface(renderer, threadSurface1);
        SDL_RenderCopy(renderer, threadText1, NULL, &videoRect);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

}

void close()
{
    SDL_DestroyTexture(threadText1);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyMutex(threadLock1);
    threadText1 = NULL;
    threadLock1 = NULL;
    window = NULL;
    renderer = NULL;
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

// SDL_Texture* Cutscene::convertCV_MatToSDL_Texture(const cv::Mat &matImg)
// {
//     IplImage opencvimg2 = (IplImage)matImg;
//     IplImage* opencvimg = &opencvimg2;

//      //Convert to SDL_Surface
//     frameSurface = SDL_CreateRGBSurfaceFrom(
//                          (void*)opencvimg->imageData,
//                          opencvimg->width, opencvimg->height,
//                          opencvimg->depth*opencvimg->nChannels,
//                          opencvimg->widthStep,
//                          0xff0000, 0x00ff00, 0x0000ff, 0);

//     if(frameSurface == NULL)
//     {
//         SDL_Log("Couldn't convert Mat to Surface.");
//         return NULL;
//     }

//     //Convert to SDL_Texture
//     frameTexture = SDL_CreateTextureFromSurface(
//                     GameEngine::getInstance()->getRenderer(), frameSurface);
//     if(frameTexture == NULL)
//     {
//         SDL_Log("Couldn't convert Mat(converted to surface) to Texture.");
//         return NULL;
//     }
//     else
//     {
//         SDL_Log("SUCCESS conversion");
//         return frameTexture;
//     }

//     cvReleaseImage(&opencvimg);
// }