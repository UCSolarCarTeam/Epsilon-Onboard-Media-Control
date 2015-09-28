#include "threadClass.hpp"
#include <cv.h>
#include "opencv2/opencv.hpp"

using namespace cv;

class VideoStream : public MyThreadClass
{
    public:
        void signalToQuit();
        IplImage *getFrame();
        bool imageReady();


    protected:
        void InternalThreadEntry();

    private:
        Mat frame;
        VideoCapture cap(0);
        bool updatedImage;
        int bufferNumber;
        IplImage threadImage1;
        IplImage threadImage2;
        IplImage threadImage3;
        int quit();

};
