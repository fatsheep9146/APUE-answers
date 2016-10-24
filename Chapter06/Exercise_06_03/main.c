#include <sys/utsname.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	struct utsname ubuf;
	if(uname(&ubuf) == -1) {
		printf("uname error\n");
		exit(1);
	}
	
	printf("sysname: %s\n", ubuf.sysname);
	printf("nodename: %s\n", ubuf.nodename);
	printf("release: %s\n", ubuf.release);
	printf("version: %s\n", ubuf.version);
	printf("machine: %s\n", ubuf.machine);
	exit(0);
}
