#!/usr/bin/python
import sys
# import pygame
# from pygame.locals import *
import time


def multiply(a,b):
    print("Will compute", a, "times", b)
    c = 0
    for i in range(0, a):
        c = c + b
    return c

def printStuff(a):
	print(a)

def playMusic(a):
	pygame.init()
	pygame.mixer.music.load('Polaris.mp3')
	pygame.mixer.music.play(0)

# playMusic("something")
# while True:
# 	pass