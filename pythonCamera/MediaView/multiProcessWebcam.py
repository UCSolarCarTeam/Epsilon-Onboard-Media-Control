import sys
import pygame
import pygame.camera
from pygame.locals import *
from multiprocessing import Pipe, Process
import time

pygame.init()
pygame.camera.init()

displayWidth = 1232    
displayHeight = 720

#1024
#576
cameraWidth = 1000
cameraHeight = 600

cameraNumber = 0

def createMainScreen():
    #create fullscreen display 640x480
    #screen = pygame.display.set_mode((displayWidth,displayHeight),pygame.FULLSCREEN|pygame.HWSURFACE)
    screen = pygame.display.set_mode((displayWidth,displayHeight))
    pygame.draw.rect(screen,(255,0,0),(0,0,displayWidth,displayHeight),1)
    return screen

def initiatePyCamera():
    cam_list = pygame.camera.list_cameras()
    webcam = pygame.camera.Camera(cam_list[cameraNumber],(cameraWidth,cameraHeight))
    webcam.start()
    return webcam

def startWebcamStream(thewebcam,childPipe,killPipe):
    while True:
        imagen = thewebcam.get_image()
        imagen = pygame.transform.flip(imagen,1,0)  #flip horizontal
        #imagen = pygame.transform.scale(imagen,(640,480))
        package = pygame.image.tostring(imagen, 'RGB')
        print("repeating")
        if (killPipe.poll()):
            print("got here")
            if (killPipe.recv() == 1):
                print("startWebcamStream: quitting...")
                break
        print("maybe here?")
        childPipe.send(package)
        print("sent package")
    print("WebcamStream quit")

def checkToQuit():
    # check for quit events
    for event in pygame.event.get():
        if event.type == pygame.QUIT or (event.type == KEYDOWN and event.key == K_ESCAPE):
            return 1

    return 0
def endProgram():
    webcam.stop()
    print("stopped webcam")
    pygame.quit()
    print("stopped pygame")
    sys.exit()


def drawWebcamImageToBuffer(image):
    xoffset = displayWidth - image.get_width()
    yoffset = 0
    screen.blit(image,(xoffset,yoffset))


screen = createMainScreen()
webcam = initiatePyCamera()
webcamSize = webcam.get_size()

parent_webcam, child_webcam = Pipe(False) #only parent can receive, only child can send
webcam_receive, webcam_sender = Pipe(False)

webcamProcess = Process(target=startWebcamStream, args=(webcam, child_webcam,webcam_receive,))


webcamProcess.start()

while True:
    update = 0

    if (parent_webcam.poll()):
        stringImage = parent_webcam.recv()
        image = pygame.image.fromstring(stringImage,webcamSize,'RGB')
        drawWebcamImageToBuffer(image)
        update = 1

    if (update == 1):
        pygame.display.update()

    quitFlag = checkToQuit()
    if (quitFlag == 1):
        webcam_sender.send(1)
        print("sent signal to kill webcam")
        time.sleep(1) 
        endProgram()



