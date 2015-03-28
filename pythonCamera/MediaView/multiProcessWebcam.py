import sys
import pygame
import pygame.camera
from pygame.locals import *
from multiprocessing import Pipe, Process

pygame.init()
pygame.camera.init()

displayWidth = 1280    
displayHeight = 720

#1024
#576
cameraWidth = 1000
cameraHeight = 600

cameraNumber = 0

def createMainScreen():
    #create fullscreen display 640x480
    screen = pygame.display.set_mode((displayWidth,displayHeight),pygame.FULLSCREEN|pygame.HWSURFACE)
    pygame.draw.rect(screen,(255,0,0),(0,0,displayWidth,displayHeight),1)
    return screen

def initiatePyCamera():
    cam_list = pygame.camera.list_cameras()
    webcam = pygame.camera.Camera(cam_list[cameraNumber],(cameraWidth,cameraHeight))
    webcam.start()
    return webcam

def startWebcamStream(thewebcam,childPipe):
    while True:
        imagen = thewebcam.get_image()
        imagen = pygame.transform.flip(imagen,1,0)  #flip horizontal
        #imagen = pygame.transform.scale(imagen,(640,480))
        childPipe.send(imagen)
        if (childPipe.poll()):
            if (childPipe.recv() == "quit"):
                break

def checkToQuit():
    # check for quit events
    for event in pygame.event.get():
        if event.type == pygame.QUIT or (event.type == KEYDOWN and event.key == K_ESCAPE):
            webcam.stop()
            pygame.quit()
            sys.exit()

def drawImageToBuffer(image):
    xoffset = displayWidth - image.get_width()
    yoffset = 0
    screen.blit(image,(xoffset,yoffset))


screen = createMainScree()
webcam = initiatePyCamera()

parent_webcam, child_webcam = Pipe()

webcamProcess = Process(target=startWebcamStream, args=(webcam, childPipe,))

while True:

    update = 0

    
