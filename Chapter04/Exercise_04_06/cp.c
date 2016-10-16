#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>


char c[1];

int main(int argc, char* argv[]) 
{
   int fd;
   int nfd;
   struct stat buf;

   if((fd = open(argv[1], O_RDONLY)) < 0) 
   {
      printf("open error\n");
      exit(1);
   }

   if((nfd = creat(argv[2], (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH))) < 0) 
   {
      printf("open error\n");
      exit(1);
   }

   if(fstat(fd, &buf) < 0)
   {
      printf("stat error\n");
      exit(1);
   }   

   int len = buf.st_size;   // The size of the file;
   int i = 0;              
   
   for(i = 0; i < len; i++) 
   {
       if(read(fd, c, 1) != 1) 
       {
          printf("read error\n");
          exit(1);
       }
       if(c[0] != '\0') 
       {
          if(write(nfd, c, 1) != 1) 
          {
             printf("write error\n");
             exit(1);
          }
       }
   }
   
   close(nfd);
   close(fd);
}
