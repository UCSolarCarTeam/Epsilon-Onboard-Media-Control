#OBJS = files to compile 
OBJS = 07_texture_loading_and_rendering.cpp 

#CC = compiler used
CC = g++

#COMPLIE_FLAGS = additional flags
COMPILE_FLAGS = -w -std=c++11

#LINK_FLAGS
LINK_FLAGS = `sdl2-config --cflags` `sdl2-config --libs` -lSDL2_image -lSDL2_mixer -ljpeg -lpng -lz -lavcodec -lavformat -lavutil

#OUTPUT_NAME = final name
OUTPUT_NAME = test

#INCLUDE FLAGS
INCLUDE_FLAGS = -Ilib

all : 
	 $(CC) $(OBJS) $(INCLUDE_FLAGS) $(LINK_FLAGS) $(COMPILE_FLAGS)  -o $(OUTPUT_NAME)

