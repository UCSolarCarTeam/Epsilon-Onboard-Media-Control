import sys
import pygame
import pygame.camera
from pygame.locals import *
from multiprocessing import Pipe, Process, Queue
import time

pygame.init()
pygame.camera.init()

displayWidth = 1232    
displayHeight = 720

#1024
#576

#640
#360
cameraWidth = 640
cameraHeight = 360

cameraNumber = 0

def createMainScreen():
    #create fullscreen display 640x480
    screen = pygame.display.set_mode((displayWidth,displayHeight),pygame.FULLSCREEN|pygame.HWSURFACE)
    #screen = pygame.display.set_mode((displayWidth,displayHeight))
    pygame.draw.rect(screen,(255,0,0),(0,0,displayWidth,displayHeight),1)
    return screen

def initiatePyCamera():
    cam_list = pygame.camera.list_cameras()
    webcam = pygame.camera.Camera(cam_list[cameraNumber],(cameraWidth,cameraHeight))
    webcam.start()
    return webcam

def startWebcamStream(thewebcam,childPipe,messageQueue):
    while True:
        streamstart = time.time()
        imagen = thewebcam.get_image()
        imagen = pygame.transform.flip(imagen,1,0)  #flip horizontal
        #imagen = pygame.transform.scale(imagen,(640,480))
        package = pygame.image.tostring(imagen, 'RGB')
        if (not messageQueue.empty()):
            print("startWebcamStream: quitting...")
            break
        beforesend = time.time()
        childPipe.send(package)
        aftersend = time.time()
        print("stream loop took: " + str(time.time()-streamstart))
        print("sending image:    " + str(aftersend - beforesend))
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
    xoffset = displayWidth - imageWidth 
    yoffset = 0
    screen.blit(image,(xoffset,yoffset))


#INITIALIZE EVERYTHING FIRST#
screen = createMainScreen()
webcam = initiatePyCamera()
webcamSize = webcam.get_size()
imageWidth = webcam.get_image().get_width()

parent_webcam, child_webcam = Pipe(False) #only parent can receive, only child can send
quitQueue = Queue()

webcamProcess = Process(target=startWebcamStream, args=(webcam, child_webcam,quitQueue,))

webcamProcess.start()


lastimagetime = 0
while True:
    mainloopstart = time.time()
    update = 0
    #print(webcam.get_size())

    if (parent_webcam.poll()):
        stringImage = parent_webcam.recv()
        image = pygame.image.frombuffer(stringImage,webcamSize,'RGB')
        drawWebcamImageToBuffer(image)
        update = 1
        print("deltatime:        " + str(time.time() - lastimagetime))
        lastimagetime = time.time()

    if (update == 1):
        pygame.display.update()

    quitFlag = checkToQuit()

    if (quitFlag == 1):
        quitQueue.put(1)
        print("sent signal to kill webcam")
        while (parent_webcam.poll()):
            parent_webcam.recv()

        webcamProcess.join(2)
        
        if(webcamProcess.is_alive()):
            print("webcam is alive still?")
            webcamProcess.terminate()
        endProgram()

    print("mainloop took:    " + str(time.time()-mainloopstart))



