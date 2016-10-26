#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int globalvar = 6;

static void my_exit(void) {
	printf("my_exit is called\n");
	fclose(stdout);
}


int main() {
	int var;
	pid_t pid;
	int ret;
	char retbuf[10];

	if(atexit(my_exit) != 0) {
		printf("atexit error\n");
		exit(1);
	}
	
	var = 88;
	printf("before vfork\n");
	if((pid = vfork()) < 0) {
		printf("vfork error\n");
		exit(1);
	}
	else if(pid == 0) {
		globalvar++;
		var++;
		_exit(0);
	}
	
	ret = printf("pid = %ld, globalvar = %d, var = %d\n", (long)getpid(), globalvar, var);
	sprintf(retbuf, "%d\n", ret);
	write(STDOUT_FILENO, retbuf, strlen(retbuf));
	exit(0);
}


