#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <time.h>

int main(int argc, char* argv[])  
{
    struct stat buf;
    struct timeval times[2];
    int fd;

    if(stat(argv[1], &buf) < 0) {
        printf("stat error\n");
        exit(1);
    }
    

    times[0].tv_sec = buf.st_atim.tv_sec;
    times[0].tv_usec = buf.st_atim.tv_nsec/1000;
    time_t cur = time(NULL);
    times[1].tv_sec = cur;
    times[1].tv_usec = 0;
    if((fd = open(argv[1], O_RDWR|O_TRUNC)) < 0) {
        printf("open error\n");
        exit(1);
    } 
  
    int ret; 
    if((ret = utimes(argv[1], times)) < 0) {
        printf("utimes error %d\n", ret);
	exit(1);
    }
    close(fd); 
    exit(0);
}
