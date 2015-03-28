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
        print("Streaming")
        imagen = thewebcam.get_image()
        imagen = pygame.transform.flip(imagen,1,0)  #flip horizontal
        #imagen = pygame.transform.scale(imagen,(640,480))
        package = pygame.image.tostring(imagen, 'RGB')
        childPipe.send(package)
        if (childPipe.poll()):
            if (childPipe.recv() == "quit"):
                break

def checkToQuit():
    # check for quit events
    for event in pygame.event.get():
        if event.type == pygame.QUIT or (event.type == KEYDOWN and event.key == K_ESCAPE):
            return 1

    return 0
def endProgram():
    webcam.stop()
    pygame.quit()
    sys.exit()

def drawWebcamImageToBuffer(image):
    xoffset = displayWidth - image.get_width()
    yoffset = 0
    screen.blit(image,(xoffset,yoffset))


screen = createMainScreen()
webcam = initiatePyCamera()
webcamSize = webcam.get_size()

parent_webcam, child_webcam = Pipe()

webcamProcess = Process(target=startWebcamStream, args=(webcam, child_webcam,))


webcamProcess.start()

while True:
    update = 0

    if (parent_webcam.poll()):
        print("received")
        stringImage = parent_webcam.recv()
        image = pygame.image.fromstring(stringImage,webcamSize,'RGB')
        drawWebcamImageToBuffer(image)
        update = 1

    if (update == 1):
        pygame.display.update()

    quitFlag = checkToQuit()
    if (quitFlag == 1):
        parent_webcam.send("quit")
        endProgram()



