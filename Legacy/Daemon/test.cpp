//includes logging routines. Can be viewed with gui using 'system log' 
#include <syslog.h> 
//for sleep command.
#include <unistd.h>
//for sprintf 
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#include<iostream>

using namespace std;

void process();

int main(int argc, char* argvalues[])
{	
	setlogmask(LOG_UPTO(LOG_NOTICE));//sets the mask to allow logging for all priorities from LOG_NOTICE and above. 

	//LOG_CONS: If a syslog call fails, the intended messaeg is instead sent to the console.
	//LOG_PID: Adds the process id to the message.
	//LOG_PERROR: Sets it so that syslog also logs errors.
	//LOG_NDELAY: opens and conncects to 
	openlog("TestDaemon",LOG_CONS|LOG_PID|LOG_NDELAY,LOG_LOCAL1); //sets identifying string, ors options, and finally the facility (user?)

	pid_t pid, sid;

   //Fork the Parent Process
    pid = fork();//pid of the child is returned to the parent. 0 is returned to the child process spawend by 'fork'.

    if (pid < 0) { exit(EXIT_FAILURE); }

    //We got a good pid, Close the Parent Process
    if (pid > 0) { exit(EXIT_SUCCESS); }

    //Change File Mask. This is the permissions of the daemon. 
    umask(0);

    //Create a new Signature Id for our child
    sid = setsid();
    if (sid < 0) { exit(EXIT_FAILURE); }

    //Change Directory
    //If we cant find the directory we exit with failure.
    if ((chdir("/")) < 0) { exit(EXIT_FAILURE); }

    //Close Standard File Descriptors
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
	
	while(true){
		process();
		sleep(120);
	}
	closelog();		
	return 0;
}

void process()
{
	syslog(LOG_NOTICE,"Process() began.");
	
	syslog(LOG_NOTICE,"Process() finished.");
}
