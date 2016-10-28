#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>


int main() {
	pid_t pid;
	int status;
	char cmd[30] = "ps aux | grep ";	
	char buf[10];


	if((pid = fork()) < 0) {
		printf("fork error\n");
		exit(1);
	}
	else if(pid == 0) {
		_exit(127);
	}

	sleep(2);
	printf("child process id %d\n", (int)pid);
	
	if(sprintf(buf, "%d", (int)pid) < 0) {
		printf("sprintf error\n");
		exit(1);
	}
	
	if(strcat(cmd, buf) < 0) {
		printf("strcat error\n");
		exit(1);
	}
	
	printf("cmd is %s\n", cmd);

	if((status = system(cmd)) < 0) {
		printf("system error\n");
		exit(1);
	}

	exit(0);
	
}
