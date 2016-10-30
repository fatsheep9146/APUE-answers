#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>


void print_ids(char *name) {
	printf("%s: pid = %ld, ppid = %ld, pgrp = %ld, tpgrp = %ld, sid = %ld\n",
		 name, (long)getpid(), (long)getppid(), (long)getpgrp(), (long)tcgetpgrp(STDIN_FILENO), (long)getsid(getpid()));
	fflush(stdout);
}

int main() {
	pid_t pid;
	pid_t pidt;	

	if((pid = fork()) < 0) {
		printf("fork error\n");
		exit(1);
	}
	else if(pid == 0) {
		if((pidt = setsid()) == -1) {
			printf("setsid error\n");
			exit(1);
		}
		print_ids("child ");
	}
	else {
		print_ids("parent");
	}
}
