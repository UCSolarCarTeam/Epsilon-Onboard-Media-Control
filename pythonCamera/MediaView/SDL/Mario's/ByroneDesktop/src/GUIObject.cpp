#include "GUIObject.h"

GUIObject::GUIObject(int xIn, int yIn, int widthIn, int heightIn)
{
	x = xIn;
	y = yIn;
	width = widthIn;
	height = heightIn;
}

void GUIObject::free()
{
	texture.free();
}

GUIObject::~GUIObject()
{
	free();
}

void GUIObject::load(std::string path)
{
	
}

void GUIObject::draw()
{
	
}

int GUIObject::getX()
{
	return x;
}

int GUIObject::getY()
{
	return y;
}
