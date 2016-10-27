#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void fun() {
	pid_t pid;
	if((pid = fork()) < 0) {
		printf("vfork error\n");
	//	exit(1);
		return ;
	}
	else if(pid == 0) {
		printf("This is child process\n");
		return ;
	}

	printf("This is parent process\n");	
	return ;
}


int main() {
	printf("Before fun()\n");
	fun();
	printf("After fun()\n");
	
}
