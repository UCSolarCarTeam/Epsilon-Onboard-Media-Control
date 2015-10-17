#include "videoStream.hpp"


VideoStream::VideoStream()
{
    m_bufferNumber = 1; 
    m_updateImage = false;

}

void VideoStream::signalToQuit()
{
    m_quit = true;
}


void VideoStream::InternalThreadEntry()
{
    VideoCapture cap(0);
    while (!m_quit)
    {
        cap >> m_frame;
        switch(m_bufferNumber)
        {
            case 1:
                m_threadImage2 = m_frame;
                m_bufferNumber = 2;
                break;
            case 2:
                m_threadImage3 = m_frame;
                m_bufferNumber = 3;
                break;
            case 3:
                m_threadImage1 = m_frame;
                m_bufferNumber = 1;
                break;
        }
        m_updateImage = true;
    }
}

bool VideoStream::imageReady()
{
    return m_updateImage;
}

IplImage *VideoStream::getFrame()
{
    m_updateImage = false;
    switch(m_bufferNumber)
    {
        case 1:
            return &m_threadImage1;
        case 2:
            return &m_threadImage2;
        case 3:
            return &m_threadImage3;
    }
}
