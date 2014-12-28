#include <iostream>
using namespace std;

//The Basic IO library.
#include <fcntl.h>
//The univesal standard library.
#include <unistd.h>
//Getting us size_t
#include <stdlib.h>
//Getting us io control (allowing us to modify camera settings).
#include <sys/ioctl.h>
//The actual V4L2 file
#include <linux/videodev2.h>
//Provides access to the integer: errno. Described by: http://man7.org/linux/man-pages/man3/errno.3.html
#include <errno.h>
//Memset
#include <string.h>
//Gives us access to timeval as well as fd_set
#include <sys/select.h>
//lets us write to files (only needed to output images)
#include <stdio.h>


//using: http://linuxtv.org/downloads/v4l-dvb-apis/common.html#open
// V4L2:
//open device
//change device properties
//negotiating data format
//negotiating io format
//actual io loop
//closing device	

//example: http://linuxtv.org/downloads/v4l-dvb-apis/capture-example.html
//Some explanation: http://www.jayrambhia.com/blog/capture-v4l2/

//to access the camera, we can test using 'streamer -o foobar.jpeg'

struct bufferdata {
        char *data;
        int length;
};


static int xioctl(int fh, int request, void *arg)
{
	int r;
	do
		r = ioctl(fh, request, arg);
	while (-1 == r && EINTR == errno);
	return r;
}

static int fd; //the file descriptor returned by open.
int main(int argc, char* argvalues[])
{
	fd=open("/dev/video0",O_RDWR /*| 0_NONBLOCK*/);
	
	if(fd==-1)
		{cout<<"Failed on camera acquisistion.\n";return 1;}
	
	//Getting device abilities.
	struct v4l2_capability capabilities; //specified by: http://linuxtv.org/downloads/v4l-dvb-apis/vidioc-querycap.html#v4l2-capability
	xioctl(fd, VIDIOC_QUERYCAP, &capabilities); 
		
	/*
	cout<<"Driver:				"<<(char*)capabilities.driver<<"\n";
	cout<<"Card:				"<<(char*)capabilities.card<<"\n";
	cout<<"Bus Info:			"<<(char*)capabilities.bus_info<<"\n";
	cout<<"Version:			"<<(int)capabilities.version<<"\n";
	cout<<"Capabilities:			"<<(int)capabilities.capabilities<<"\n";
	cout<<"Device Caps:			"<<(int)capabilities.device_caps<<"\n";
	*/
	
	
	//The CAP_DEVICES_CAPS flag is set only for capabilities and never for device_cap. 
	/*
	cout<<"All capabilities enabled: "<<((int)(~capabilities.device_caps&capabilities.capabilities)==V4L2_CAP_DEVICE_CAPS)<<"\n";
	
	cout<<"Supports vid. capture:		"<<((V4L2_CAP_VIDEO_CAPTURE&capabilities.device_caps)!=0)<<"\n";
	cout<<"Supports mplane. capture:	"<<((V4L2_CAP_VIDEO_CAPTURE_MPLANE&capabilities.device_caps)!=0)<<"\n";
	cout<<"Supports video overlay:		"<<((V4L2_CAP_VIDEO_OVERLAY&capabilities.device_caps)!=0)<<"\n";	
	cout<<"Supports read/write io:		"<<((V4L2_CAP_READWRITE&capabilities.device_caps)!=0)<<"\n";	
	cout<<"Supports audio capture:		"<<((V4L2_CAP_AUDIO&capabilities.device_caps)!=0)<<"\n";	
	cout<<"Supports streaming:		"<<((V4L2_CAP_STREAMING&capabilities.device_caps)!=0)<<"\n";
	*/
	 
	
	//OBtaining format information
	struct v4l2_format fmt;
	memset(&fmt,0,sizeof(fmt));
	
	fmt.type=V4L2_BUF_TYPE_VIDEO_CAPTURE;
	
	//Setting format specifiers
	
	cout<<"Getting format: "<<(xioctl(fd, VIDIOC_G_FMT, &fmt)!=-1)<<"\n";
	
	if(true){//setting a higher resolution.
		fmt.fmt.pix.width=1280;
		fmt.fmt.pix.height=720;
		xioctl(fd,VIDIOC_S_FMT, &fmt);
	}
	
	v4l2_pix_format pixfmt=fmt.fmt.pix;
	
	cout<<"width: 				"<<pixfmt.width<<"\n";
	cout<<"height: 			"<<pixfmt.height<<"\n";
	char* pixelfmt = (char*)&pixfmt.pixelformat;
	cout<<"pixelformat: 		";for(int i =0; i < 4; i++)cout<<pixelfmt[i];cout<<"\n";
	cout<<"image size: 			"<<pixfmt.sizeimage<<"\n";
	
	
	//obtaining buffer information!
	struct v4l2_requestbuffers reqbuf; //specified by: http://linuxtv.org/downloads/v4l-dvb-apis/vidioc-reqbufs.html
	memset (&reqbuf, 0, sizeof (reqbuf));
	reqbuf.count=4;
	reqbuf.memory = V4L2_MEMORY_USERPTR;
	reqbuf.type=fmt.type;
	xioctl(fd, VIDIOC_REQBUFS, &reqbuf);
	cout<<"Buffer count: "<<reqbuf.count<<"\n";
	
	//Creating buffers!
	struct v4l2_buffer* buffers = new v4l2_buffer[reqbuf.count];
	bufferdata* bufferdatas = new bufferdata[reqbuf.count];
	
	for(int i = 0; i < reqbuf.count; i++){
		bufferdatas[i].length=pixfmt.sizeimage;
		bufferdatas[i].data=new char[bufferdatas[i].length];
		
		memset(&buffers[i],0,sizeof(buffers[i]));
		buffers[i].type=fmt.type;
		buffers[i].memory = reqbuf.memory;
		buffers[i].index=i;
		buffers[i].m.userptr = (unsigned long)bufferdatas[i].data;
		buffers[i].length=bufferdatas[i].length;
		xioctl(fd, VIDIOC_QBUF, &buffers[i]);//adding our buffer to the q
	}
	xioctl(fd,VIDIOC_STREAMON,&fmt.type);
	
	//Main loop:
	
	int totalFrames = 11;
	int frames = 0; 
	int lastLoaded=-1;//we will not need this soon enough.
	while(++frames<=totalFrames) {
		while(true) {
			fd_set fdset;
			struct timeval tv;
			FD_ZERO(&fdset);//zeroes our set of file descriptors.
			FD_SET(fd,&fdset);
			//Setting interval
			tv.tv_sec=1;
			tv.tv_usec=0;
			
			//select takes this form: 
			//select(nfds,&readfds,&writefds,&exceptfds,&timeout)
			//nfds is the highest file description in any of the sets, plus one.
			//readfds watches these file descriptors for read acess,
			//writefds watches for write access
			//except for exception access
			//timeout specifies the length of time to wait.
			int result = select(fd+1,&fdset,NULL,NULL,&tv);
			//result is the number of file descriptors that won't block with their respective actions.
			if(result==-1){//error!?
				if(errno == EINTR)//we allow another attempt if we are interrupted. 
					continue;
				return errno;
			}
			if(result==0){//timeout
				cout<<"Timeout.\n";
				break;
			}
			
			struct v4l2_buffer buf;
			memset(&buf,0,sizeof(buf));
			buf.type=fmt.type;
			buf.memory=reqbuf.memory;
			
			//VIDIOC_DQBUF takes a partially filled in buffer (in this case, 'buf' and fills in the remaining details)
			xioctl(fd,VIDIOC_DQBUF,&buf);	
			
			//==do image processing here 
			lastLoaded=buf.index;
			//(char*)buf.m.userptr
			//buf.bytesused 
			
			xioctl(fd,VIDIOC_QBUF,&buf);
			
			break;
		}
	}
	
	
	//saving a copy of our last image!
	if(lastLoaded!=-1){
		FILE *imagefile = fopen("last.ppm","wb");//"wb" indicates write and binary mode.
		fprintf(imagefile,"P6 %d %d 255\n",pixfmt.width,pixfmt.height);
		unsigned char t[6];
		for(int i = 0; i < pixfmt.sizeimage; i+=2){//jumping by two to capture only the lumen data.
			//from http://en.wikipedia.org/wiki/YUV#Converting_between_Y.27UV_and_RGB
			memset(&t,bufferdatas[lastLoaded].data[i],sizeof(t));
			fwrite(t,1,6,imagefile);//(elements,size,number,file)
		}
	}
	
	
	//Cleaning up!
	xioctl(fd,VIDIOC_STREAMOFF,&fmt.type);
	for(int i = 0; i < reqbuf.count; i++){
		delete[] bufferdatas[i].data;
	}
	delete[] bufferdatas;
	delete[] buffers;
	close(fd);
	cout<<"errorno: "<<errno<<"\n";	
	return 0;
}

