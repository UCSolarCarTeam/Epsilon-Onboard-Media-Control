#include "videoStream.hpp"

VideoStream::VideoStream()
{
    bufferNumber = 1; 
    updatedImage = false;

}

void VideoStream::signalToQuit()
{
    quit = 1;
}


void VideoStream::InternalThreadEntry()
{
    while (!quit)
    {
        cap >> frame;
        switch(bufferNumber)
        {
            case 1:
                threadImage2 = frame;
                bufferNumber = 2;
                break;
            case 2:
                threadImage3 = frame;
                bufferNumber = 3;
                break;
            case 3:
                threadImage1 = frame;
                bufferNumber = 1;
                break;
        }
        updatedImage = true;
    }
    return 0;
}

bool VideoStream::imageReady()
{
    return updatedImage;
}

IplImage *VideoStream::getFrame()
{
    updatedImage = false;
    switch(bufferNumber)
    {
        case 1:
            return &threadImage1;
        case 2:
            return &threadImage2;
        case 3:
            return &threadImage3;
    }
}
