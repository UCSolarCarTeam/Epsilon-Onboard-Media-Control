#ifndef GUIOBJECT_H
#define GUIOBJECT_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "MText.h"

class GUIObject {
	
	public:
		GUIObject(int xIn, int yIn, int widthIn, int heightIn);
		~GUIObject();
		void load(std::string path);
		void setRenderer(SDL_Renderer* renderer);
		void draw();
		void free();
		int getX();
		int getY();
	private:
		int x, y, width, height;
		MText texture;
};

#endif
