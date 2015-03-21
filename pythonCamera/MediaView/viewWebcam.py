#!/usr/bin/python
import sys
import pygame
import pygame.camera
from pygame.locals import *


pygame.init()
pygame.camera.init()

displayWidth = 1280    
displayHeight = 720

#1024
#576
cameraWidth = 1000
cameraHeight = 600

def createMainScreen():
    #create fullscreen display 640x480
    screen = pygame.display.set_mode((displayWidth,displayHeight),pygame.FULLSCREEN|pygame.HWSURFACE)
    pygame.draw.rect(screen,(255,0,0),(0,0,displayWidth,displayHeight),1)
    return screen

def initiatePyCamera():
    cam_list = pygame.camera.list_cameras()
    webcam = pygame.camera.Camera(cam_list[0],(cameraWidth,cameraHeight))
    webcam.start()
    return webcam

def getImage():
    imagen = webcam.get_image()
    imagen = pygame.transform.flip(imagen,1,0)  #flip horizontal
    #imagen = pygame.transform.scale(imagen,(640,480))
    return imagen

def drawImageToBuffer():
    xoffset = displayWidth - imagen.get_width()
    yoffset = 0
    screen.blit(imagen,(xoffset,yoffset))

def checkToQuit():
    # check for quit events
    for event in pygame.event.get():
        if event.type == pygame.QUIT or (event.type == KEYDOWN and event.key == K_ESCAPE):
            webcam.stop()
            pygame.quit()
            sys.exit()

screen = createMainScreen()
webcam = initiatePyCamera()

pygame.mixer.music.load('Polaris.mp3')
pygame.mixer.music.play(0)


while True:
    imagen = getImage()
    drawImageToBuffer()
    pygame.display.update()
    checkToQuit()

