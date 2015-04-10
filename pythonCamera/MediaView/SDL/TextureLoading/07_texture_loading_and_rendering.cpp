/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

#include "opencv2/opencv.hpp"
#include <cv.h>
#include <highgui.h>

using namespace cv;

//Screen dimension constants
const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 540;

const int VIDEO_WIDTH = 960;
const int VIDEO_HEIGHT = 540;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Current displayed texture
SDL_Texture* gTexture = NULL;
SDL_Surface* tempSurface = NULL;

//Shared Mat
Mat sharedFrame;
SDL_bool condition = SDL_FALSE;
SDL_mutex* threadLock1 = NULL;
SDL_cond* threadCond1 = NULL;



VideoCapture cap(0);


bool init()
{
	//Initialization flag
	bool success = true;

    if(!cap.isOpened())  // check if we succeeded
    	return -1;
    else
    	printf("Video Opened\n");

    cap.set(CV_CAP_PROP_FRAME_WIDTH, VIDEO_WIDTH);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, VIDEO_HEIGHT); 

	//Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
    	printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
    	success = false;
    }
    else
    {
		//Set texture filtering to linear
    	if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
    	{
    		printf( "Warning: Linear texture filtering not enabled!" );
    	}

		//Create window
		//gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    	gWindow = SDL_CreateWindow("Test SDL 2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, cap.get(CV_CAP_PROP_FRAME_WIDTH)
									, cap.get(CV_CAP_PROP_FRAME_HEIGHT), SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL); //for raspberry
    	if( gWindow == NULL )
    	{
    		printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
    		success = false;
    	}
    	else
    	{
			//Create renderer for window
    		gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
    		if( gRenderer == NULL )
    		{
    			printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
    			success = false;
    		}
    		else
    		{
				//Initialize renderer color
    			SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
    			int imgFlags = IMG_INIT_PNG;
    			if( !( IMG_Init( imgFlags ) & imgFlags ) )
    			{
    				printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
    				success = false;
    			}
    		}
    	}

    	threadLock1 = SDL_CreateMutex();
    }


    return success;

}

bool loadMedia()
{
	bool success = true;
	SDL_DestroyTexture( gTexture );

	// Mat frame;
 //    cap >> frame; 					// get a new frame
    IplImage ipl_frame = sharedFrame;		// turn into ipl image
    IplImage* img = &ipl_frame;  	
    

    // cv::Size size = frame.size();

    // int total = size.width * size.height * frame.channels();
    // std::cout << "Mat size = " << total << std::endl;

    // std::vector<uchar> data(frame.ptr(), frame.ptr() + total);
    // std::string s(data.begin(), data.end());                   
    // std::cout << "String size = " << s.length() << std::endl;
    //std::cout << s << std::endl;

   // printf("%s",img->imageData);

    tempSurface = SDL_CreateRGBSurfaceFrom((void*)img->imageData,
    	img->width,
    	img->height,
    	img->depth * img->nChannels,
    	img->widthStep,
    	0xff0000, 0x00ff00, 0x0000ff, 0
    	);


    gTexture = SDL_CreateTextureFromSurface(gRenderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    if( gTexture == NULL )
    {
    	printf( "Unable to create texture from! SDL Error: %s\n", SDL_GetError() );
    }


    return success;
}

void close()
{
	//Free loaded image
	SDL_DestroyTexture( gTexture );
	gTexture = NULL;

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int CameraStream(void* data) 
{
	while (true)
	{
		cap >> sharedFrame;
		printf("looping");
		SDL_LockMutex(threadLock1);

		condition = SDL_TRUE;
		SDL_CondSignal(threadCond1);
		SDL_UnlockMutex(threadLock1);
	}
	return 0;
}


int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{

    	SDL_Thread* threadID = SDL_CreateThread(CameraStream, "Backup Camera Thread", NULL);

			//Main loop flag
		bool quit = false;

			//Event handler
		SDL_Event e;

			//While application is running
		while( !quit )
		{
				//Handle events on queue
			while( SDL_PollEvent( &e ) != 0 )
			{
					//User requests quit
				if( e.type == SDL_QUIT )
				{
					quit = true;
				}
			}

			SDL_LockMutex(threadLock1);
			while (!condition) {
				SDL_CondWait(threadCond1, threadLock1);
			}
			condition = SDL_FALSE;
			if( !loadMedia() ){
				printf( "Failed to load media!\n" );
			}
			SDL_UnlockMutex(threadLock1);


				//Clear screen
				//SDL_RenderClear( gRenderer );

				//Render texture to screen
			SDL_RenderCopy( gRenderer, gTexture, NULL, NULL );

				//Update screen
			SDL_RenderPresent( gRenderer );
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}