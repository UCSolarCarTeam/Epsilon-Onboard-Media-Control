#include "MCameraText.h"

static int camCount = 0;

MCameraText::MCameraText()
{
	if (camCount > 0)
		mainFocus = false;
	else
		mainFocus = true;
	camId = camCount;
	camCount++;
}

MCameraText::~MCameraText()
{
	free();
}

bool MCameraText::render2(IplImage* img)
{
	SDL_Texture* texture = NULL;
	SDL_RenderClear(getRenderer());
	SDL_Surface* surface = SDL_CreateRGBSurfaceFrom((void*)img->imageData,
					img->width,
					img->height,
					img->depth * img->nChannels,
					img->widthStep,
					0xff0000, 0x00ff00, 0x0000ff, 0
					);
	if (surface == NULL)
		return false;
	texture = SDL_CreateTextureFromSurface(getRenderer(), surface);
	if (texture == NULL)
		return false;
	SDL_LockTexture(texture, NULL, &surface->pixels, &surface->pitch);
	if (mainFocus)
	{
		videoRect.x = 0;
		videoRect.y = 0;
		videoRect.w = 640;
		videoRect.h = 480;
		
	}
	
	else
	{
		videoRect.x = 640 * camId; //change based on num cameras
		videoRect.y = 0; //change based on num cameras
		videoRect.w = 200; //dummy value
		videoRect.h = 200; //dummy value
	}
	SDL_RenderCopy(getRenderer(), texture, NULL, &videoRect);
	SDL_UnlockTexture(texture);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
	return true;
}

void MCameraText::free()
{
	MText::free();
}

int MCameraText::getCamId()
{
	return camId;
}

int MCameraText::getCamCount()
{
	return camCount;
}
