#include <highgui.h>
#include <cv.h>
#include "opencv2/opencv.hpp"
#include "MText.h"
#include "MCameraText.h"
extern "C" {
	#include <SDL.h>
	#include <SDL_thread.h>
	#include <SDL_image.h>
	#include "libavcodec/avcodec.h"
	#include "libavformat/avformat.h"
}
#include <iostream>
#include <stdio.h>
//#include <vector>
bool sick = true;
using namespace cv;

// Necessary definitions
#define SDL_AUDIO_BUFFER_SIZE 1024
#define AVCODEC_MAX_AUDIO_FRAME_SIZE 192000
#define SCREEN_HEIGHT 720
#define SCREEN_WIDTH 1440
#define MAX_CAMERAS 10


/* TODO: make an add camera function (have it increment a port number?) 
 * 		 change main loop so that it will render regardless of the video 
 * 		 being finished
 * 		 IMPORTANT: make arrays for the contexts and everything doubled
 * 		 with the size of the max number of cameras, and change functions
 * 		 to use arrays. MCameraText does not work well, maybe ditch?  */

void close();

int videoStream = -1;
int audioStream = -1;
int quit = 0;

SDL_Texture* texture = NULL;

SDL_Renderer* renderer = NULL;
SDL_Window* window = NULL;
MText test;
MCameraText camera0;
MCameraText camera1;

SDL_Rect videoRect;
SDL_Rect tempRect;

AVFormatContext* ctxArray[MAX_CAMERAS] = {NULL};	// context array for all cameras
IplImage* imageArray[MAX_CAMERAS];		// image array for all cameras

AVFormatContext* pFormatCtx = NULL;


AVFormatContext* pFormatCtx2 = NULL;


/***********************************************************************
/*							SDL functions 
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
	
	test.setRenderer(renderer);
	if (!test.loadFromFile("assets/object.png"))
		printf("an error has occured");
	camera0.setRenderer(renderer);
	camera1.setRenderer(renderer);
	
	return success;
}

// Shows an individual frame of the supplied video
void show_frame(IplImage* img, IplImage* img2)
{	
	SDL_RenderClear(renderer);
	SDL_Rect r;
	r.x = 600;
	r.y = 600;
	r.w = 200;
	r.h = 200;
	
	SDL_Surface* surface = SDL_CreateRGBSurfaceFrom((void*)img->imageData,
					img->width,
					img->height,
					img->depth * img->nChannels,
					img->widthStep,
					0xff0000, 0x00ff00, 0x0000ff, 0
					);
	SDL_Surface* surface2 = SDL_CreateRGBSurfaceFrom((void*)img2->imageData,
					img2->width,
					img2->height,
					img2->depth * img2->nChannels,
					img2->widthStep,
					0xff0000, 0x00ff00, 0x0000ff, 0
					);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_Texture* texture2 = SDL_CreateTextureFromSurface(renderer, surface2);
	SDL_FreeSurface(surface);
	SDL_FreeSurface(surface2);
	SDL_RenderCopy(renderer, texture, NULL, &videoRect);
	SDL_RenderCopy(renderer, texture2, NULL, &r);
	//test.render(0, SCREEN_HEIGHT - test.getHeight());
	//camera0.render2(img);
	//camera1.render2(img);
	SDL_RenderPresent(renderer);
	
	//SDL_RenderFillRect(renderer, &r);
	//SDL_RenderPresent(renderer);
}


/***********************************************************************
 * 
 * *********************************************************************/
 
 
void setup_ffmpeg(char* filename, char* filename2)
{
	for (int i = 0; i < MCameraText::getCamCount(); i++)
	{
		if (avformat_open_input(&ctxArray[i], filename, NULL, NULL) != 0)
		{
			fprintf(stderr, "FFmpeg failed to open file %s!\n", filename);
			exit(-1); 
		}
	
		
		if (avformat_find_stream_info(ctxArray[i], NULL) < 0)
		{
			fprintf(stderr, "FFmpeg failed to retrieve stream info!\n");
			exit(-1); 
		}
		
	}
	/*
	if (avformat_open_input(&pFormatCtx2, filename2, NULL, NULL) != 0)
    {
        fprintf(stderr, "FFmpeg failed to open file %s!\n", filename2);
        exit(-1); 
    }
	*/
	/*
    if (avformat_find_stream_info(pFormatCtx, NULL) < 0)
    {
        fprintf(stderr, "FFmpeg failed to retrieve stream info!\n");
        exit(-1); 
    }
    
    if (avformat_find_stream_info(pFormatCtx2, NULL) < 0)
    {
        fprintf(stderr, "FFmpeg failed to retrieve stream info!\n");
        exit(-1); 
    }*/

    // Dump information about file onto standard error
    av_dump_format(ctxArray[0], 0, filename, 0);
    av_dump_format(ctxArray[1], 0, filename2, 0);

    // Find the first video stream
    for (int i = 0; i < MCameraText::getCamCount(); i++)
    {
		for (int j = 0; j < ctxArray[i]->nb_streams; j++)
		{
			if (ctxArray[i]->streams[j]->codec->codec_type == AVMEDIA_TYPE_VIDEO && videoStream < 0) 
			{
				videoStream = j;
				
			}
		
			if (ctxArray[i]->streams[j]->codec->codec_type == AVMEDIA_TYPE_AUDIO && audioStream < 0) 
			{
				audioStream = j;
			}
			
		}
    }
    /*
    i = 0;
    for (i; i < pFormatCtx2->nb_streams; i++)
    {
        if (pFormatCtx2->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO && videoStream < 0) 
        {
            videoStream = i;
        }
		
        if (pFormatCtx2->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO && audioStream < 0) 
        {
            audioStream = i;
        }
    }
	*/
    if (videoStream == -1)
    {
        fprintf(stderr, "No video stream found in %s!\n", filename);
        exit(-1); 
    }  

    if (audioStream == -1)
    {
        fprintf(stderr, "No audio stream found in %s!\n", filename);
        exit(-1); 
    }  

}

int main(int argc, char* argv[])
{
	
	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s <video>\n", argv[0]);
		return -1;
	}
	av_register_all();
	
	if (!init_SDL())
	{
		fprintf(stderr, "Could not initialize SDL!\n");
		return -1;
	}
	
	setup_ffmpeg(argv[1], argv[2]);

	VideoCapture cap(argv[1]);
	VideoCapture cap2(argv[2]);
	
	if (!cap.isOpened())
	{
		fprintf(stderr, "Failed to load file!\n");
		return -1;
	}
	
	AVPacket packet;
	// read frame is undefined
	while (true)
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
	// make this take from an array based on each context / packet?
	/*while*/ if(av_read_frame(ctxArray[0], &packet) != -10)
	{
		/*
		if (packet.stream_index == videoStream)
		{	*/
              // Actually this is were SYNC between audio/video would happen.
              // Right now I assume that every VIDEO packet contains an entire video frame, and that's not true. A video frame can be made by multiple packets!
              // But for the time being, assume 1 video frame == 1 video packet,
              // so instead of reading the frame through ffmpeg, I read it through OpenCV. 
              Mat frame;
              Mat frame2;
              cap >> frame; // get a new frame
              cap2 >> frame2;
              IplImage ipl_frame = frame;
              IplImage ipl_frame2 = frame2;
			  show_frame(&ipl_frame, &ipl_frame2);
			  cvWaitKey(25 / MCameraText::getCamCount()); //any way to do this naturally?
			  
			  av_free_packet(&packet);
			  
			  
		//}
		
		/*else if (packet.stream_index == audioStream)
		{
			packet_queue_put(&audioq, &packet);
		}*/
		/*
		else
		{
			av_free_packet(&packet);
		}*/
	}
	
	else
	{
		
		
	}

	}
	

	
	
    // the camera will be deinitialized automatically in VideoCapture destructor


    // Close the codec

    // Close the video file
   avformat_close_input(&pFormatCtx);
   for (int i = 0; i < MAX_CAMERAS; i++)
   {
	   avformat_close_input(&ctxArray[i]);
   }

    return 0;
}

void close()
{
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
