#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main() 
{
	time_t now;
	struct tm *tptr1;
	char buf1[80];

	time(&now);
	tptr1 = localtime(&now);
	now += 10000;	

	if(strftime(buf1, 80, "time and date: %r, %a %b %d, %Y, %Z", tptr1) == 0) {
		printf("buffer length is small\n");
	}
	else {
		printf("%s\n", buf1);
	}


}
