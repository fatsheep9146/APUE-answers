#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <time.h>

#define FILE_MODE       (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define DIR_MODE        (FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH)


int main(int argc, char* argv[]) {
    long PATH_MAX = pathconf(".", _PC_PATH_MAX);
    int depth = atoi(argv[2]);
    char *file = argv[1];
    char path[PATH_MAX];
    path[0] = '.';
    path[1] = '/';
    path[2] = '\0';
    strcat(path, file); 
    char *curpath;
   
    int i = 0;   
    for(i = 0; i < depth; i++) {
        mkdir(path, DIR_MODE);
        printf("depth %d is built\n", i);
        chdir(path);
    }

}
