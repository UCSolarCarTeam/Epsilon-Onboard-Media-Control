#!/usr/bin/python
import sys
import pygame
import pygame.camera
from pygame.locals import *


pygame.init()
pygame.camera.init()

displayWidth = 1280    
displayHeight = 720

cameraWidth = 1000
cameraHeight = 600


#create fullscreen display 640x480
screen = pygame.display.set_mode((displayWidth,displayHeight),pygame.FULLSCREEN|pygame.HWSURFACE)


cam_list = pygame.camera.list_cameras()
webcam = pygame.camera.Camera(cam_list[1],(cameraWidth,cameraHeight))
webcam.start()

while True:

    pygame.draw.rect(screen,(255,0,0),(0,0,displayWidth,displayHeight),1)
    #grab image, scale and blit to screen
    imagen = webcam.get_image()
    #imagen = pygame.transform.scale(imagen,(640,480))
    print(imagen.get_width())
    print(imagen.get_height())

    xoffset = displayWidth - imagen.get_width()
    yoffset = 0
    screen.blit(imagen,(xoffset,yoffset))

    #draw all updates to display
    pygame.display.update()

    # check for quit events
    for event in pygame.event.get():
        if event.type == pygame.QUIT or (event.type == KEYDOWN and event.key == K_ESCAPE):
            webcam.stop()
            pygame.quit()
            sys.exit()
