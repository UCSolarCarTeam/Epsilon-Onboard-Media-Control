#include "MText.h"

MText::MText()
{
	texture = NULL;
	renderer = NULL;
	width = 0;
	height = 0;
}

MText::~MText()
{
	free();
}

bool MText::loadFromFile(std::string path)
{
	free();
	
	SDL_Texture* newTexture  = NULL;
	
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s. SDL_Image error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s. SDL_Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			width = loadedSurface->w;
			height = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	texture = newTexture;
	return texture != NULL;
}

void MText::free()
{
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
		renderer = NULL;
		width = 0;
		height = 0;
	}
}

void MText::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod(texture, red, green, blue);
}

void MText::setBlendMode(SDL_BlendMode blend)
{
	SDL_SetTextureBlendMode(texture, blend);
}

void MText::setAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(texture, alpha);
}

void MText::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* centre, SDL_RendererFlip flip)
{
	SDL_Rect renderQuad = {x, y, width, height};
	if(clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, centre, flip);
}

int MText::getWidth()
{
	return width;
}

int MText::getHeight()
{
	return height;
}

void MText::setRenderer(SDL_Renderer* rendererIn)
{
	renderer = rendererIn;
}

SDL_Renderer* MText::getRenderer()
{
	return renderer;
}

SDL_Texture* MText::getTexture()
{
	return texture;
}
