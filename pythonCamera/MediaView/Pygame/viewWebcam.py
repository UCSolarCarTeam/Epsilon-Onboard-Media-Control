#!/usr/bin/python
import sys
import pygame
import pygame.camera
from pygame.locals import *
import time
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

pygame.init()
pygame.camera.init()

displayWidth = 1232    
displayHeight = 720

#1024
#576
cameraWidth = 640
cameraHeight = 360

cameraNumber = 0

def createMainScreen():
    #create fullscreen display 640x480
    #screen = pygame.display.set_mode((displayWidth,displayHeight),pygame.FULLSCREEN|pygame.HWSURFACE)
    screen = pygame.display.set_mode((displayWidth,displayHeight),pygame.FULLSCREEN)
    pygame.draw.rect(screen,(255,0,0),(0,0,displayWidth,displayHeight),1)
    return screen

def initiatePyCamera():
    cam_list = pygame.camera.list_cameras()
    webcam = pygame.camera.Camera(cam_list[cameraNumber],(cameraWidth,cameraHeight))
    webcam.start()
    theWebcam = webcam
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

def playMusic():
    pygame.mixer.music.load('Polaris.mp3')
    pygame.mixer.music.play(0)

screen = createMainScreen()
#webcam = initiatePyCamera()
webcam = initiatePyCamera()

#pygame.mixer.music.load('Polaris.mp3')
#pygame.mixer.music.play(0)
endloop = 0

while True:
     
    
    beforeimage = time.time()
    imagen = getImage()
    afterimage = time.time()
    drawImageToBuffer()
    afterdraw = time.time()
    pygame.display.update()
    afterdisplay = time.time()
    checkToQuit()

    print("Get Image: " + str(afterimage - beforeimage))    
    print("Draw Image:" + str(afterdraw - afterimage))
    print("After Disp:" + str(afterdisplay - afterdraw))
    print("------ loop took: " + str(time.time()- endloop) + "-------")
    endloop = time.time()


