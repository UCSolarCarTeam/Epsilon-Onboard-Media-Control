#!/usr/bin/python
import sys
import pygame
import pygame.camera
from pygame.locals import *


pygame.init()
pygame.camera.init()

screenWidth = 1920
screenHeight = 1080

xwidth = 1920    
yheight = 1080

#create fullscreen display 640x480
screen = pygame.display.set_mode((screenWidth,screenHeight),pygame.FULLSCREEN|pygame.HWSURFACE)

cam_list = pygame.camera.list_cameras()
webcam = pygame.camera.Camera(cam_list[0],(xwidth,yheight))
webcam.start()

while True:
   #grab image, scale and blit to screen
   imagen = webcam.get_image()
   #imagen = pygame.transform.scale(imagen,(1920,1080))
   screen.blit(imagen,(0,0))

   #draw all updates to display
   pygame.display.update()

   # check for quit events
   for event in pygame.event.get():
       if event.type == pygame.QUIT or (event.type == KEYDOWN and event.key == K_ESCAPE):
         webcam.stop()
         pygame.quit()
         sys.exit()
