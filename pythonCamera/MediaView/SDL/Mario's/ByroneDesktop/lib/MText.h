#ifndef MTEXT_H
#define MTEXT_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class MText 
{
	public:
		MText();
		~MText();
		bool loadFromFile(std::string path);
		void free();
		void setColor(Uint8 red, Uint8 green, Uint8 blue);
		void setBlendMode(SDL_BlendMode blend);
		void setAlpha(Uint8 alpha);
		void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* centre = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
		int getWidth();
		int getHeight();
		void setRenderer(SDL_Renderer* rendererIn);
		SDL_Renderer* getRenderer();
		SDL_Texture* getTexture();
	private:
		SDL_Texture* texture;
		SDL_Renderer* renderer;
		int width;
		int height;


};
#endif
