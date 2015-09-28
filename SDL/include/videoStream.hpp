#ifndef VIDEOSTREAM_H
#define VIDEOSTREAM_H 

#include "threadClass.hpp"
#include <cv.h>
#include "opencv2/opencv.hpp"

using namespace cv;

class VideoStream : public MyThreadClass
{
    public:
        VideoStream();
        void signalToQuit();
        IplImage *getFrame();
        bool imageReady();


    protected:
        void InternalThreadEntry();

    private:
        Mat m_frame;
        bool m_updateImage;
        int m_bufferNumber;
        IplImage m_threadImage1;
        IplImage m_threadImage2;
        IplImage m_threadImage3;
        bool m_quit;

};

#endif
