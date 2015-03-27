#!/usr/bin/python
import sys
import pygame
import pygame.camera
from pygame.locals import *

'''
In this MediaPlayer version. We will have three subwindows existing in a main window (to my current knowledge)
Current planning: We will have 3 sub surfaces and 1 main surface (which is default)

The main surface will be named 'screen' and is set by 'pygame.display.set_mode()' 

The 3 subsurfaces (which are just normal surfaces):
    - Music Player
    - Webcam Video
    - GPS updater

Also planning to have screen being updated on the main process/thread while the the other 
three processes will handle the Music Player, Webcam Video, and GPS Updater respectively
'''

    


if __name__ == '__main__':

