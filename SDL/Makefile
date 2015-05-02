#OBJS = files to compile 
OBJS = src/Main.cpp

#CC = compiler used
CC = g++

#COMPLIE_FLAGS = additional flags
COMPILE_FLAGS = -w -g -std=c++0x -O3

LINK_FLAGS = `sdl2-config --cflags` `sdl2-config --libs` `pkg-config opencv --cflags` `pkg-config opencv --libs` -lSDL2_image -lSDL2_mixer -ltiff -ljpeg -lpng -lz -lavcodec -lavformat -lavutil


#OUTPUT_NAME = final name
OUTPUT_NAME = main

#INCLUDE FLAGS
INCLUDE_FLAGS = -Ilib -Iinclude

all : 
	 $(CC) $(OBJS) $(INCLUDE_FLAGS) $(LINK_FLAGS) $(COMPILE_FLAGS)  -o $(OUTPUT_NAME)

clean :
	rm main

