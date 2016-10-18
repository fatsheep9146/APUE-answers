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

char *num[30] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10",
                 "11", "12", "13", "14", "15", "16", "17", "18", "19", "20",
		 "21", "22", "23", "24", "25", "26", "27", "28", "29", "30"};

int main(int argc, char* argv[]) {
    long PATH_MAX = pathconf(".", _PC_PATH_MAX);
    int depth = atoi(argv[2]);
    char *file = "longlonglonglonglonglonglonglonglonglonglonglonglonglonglonglonglonglonglonglonglonglonglonglonglonglonglonglonglonglonglonglonglonglonglonglonglonglonglonglonglonglonglonglonglonglonglonglonglonglonglonglonglonglonglonglonglonglonglonglong";
    char path[PATH_MAX];
    path[0] = '.';
    path[1] = '/';
    path[2] = '\0';
    strcat(path, file); 
    char *curpath;
   
    int i = 0;   
    for(i = 0; i < depth; i++) {
        curpath = (char *)malloc(400*sizeof(char));
        strcpy(curpath, path);
        strcat(curpath, num[i]);
        mkdir(curpath, DIR_MODE);
        printf("depth %d is built\n", i);
        chdir(curpath);
        free(curpath);
    }

    file = "file1.txt";
    if(creat(file, FILE_MODE) < 0) {
        printf("creat error\n");
        exit(1);
    }

    printf("%ld\n", pathconf("/", _PC_PATH_MAX));

    char *npath = (char *)malloc(PATH_MAX*sizeof(char));
    if(getcwd(npath, PATH_MAX) == NULL) {
        printf("getcwd error\n");
        printf("%d\n", strlen(npath));
        printf("%s\n", npath);
        free(npath);
        exit(1);
    }
   
    printf("%d\n", strlen(npath));
    printf("%s\n", npath);
    free(npath);
      
}
