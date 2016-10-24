#include <time.h>
#include <stdio.h>

int main() {
	time_t t;
	struct tm* tptr;
	char buf[80];
	
	time(&t);
	tptr = localtime(&t);
	strftime(buf, 80, "%a %b %d %T %Z %Y", tptr);
	printf("%s\n", buf);
}
