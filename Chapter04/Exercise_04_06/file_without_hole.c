#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

char buf1[] = "abcdefgh";
char buf2[] = "ABCDEFGH";
char zero[] = "\0";

int main(int argc, char *argv[]) 
{
    int fd;
    if((fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC)) < 0) {
        printf("open error\n");
        exit(1);	
    }

    if(write(fd, buf1, strlen(buf1)) != strlen(buf1)) {
        printf("write buf1 error\n");
        exit(1);
    }

    int i;
    for(i = 0; i < 16376; i++) 
    {
       write(fd, zero, 1);
    }

    if(write(fd, buf2, strlen(buf2)) != strlen(buf2)) {
        printf("write buf2 error\n");
        exit(1);
    }

    close(fd);
}
