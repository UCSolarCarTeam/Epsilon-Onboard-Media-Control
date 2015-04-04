#ifndef MCAMERATEXT_H
#define MCAMERATEXT_H

#include "MText.h"
#include <cv.h>
#include <SDL.h>

class MCameraText: public MText 
{
	public:
		MCameraText();
		~MCameraText();
		bool render2(IplImage* img);
		void free();
		int getCamId();
		static int getCamCount();
	private:	
		SDL_Rect videoRect;
		bool mainFocus;
		int camId;
};

#endif
