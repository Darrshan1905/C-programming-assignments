#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include <unistd.h>
#include "sys/syscall.h"
#include<stdarg.h>

#define BUFSIZE 100

void error(char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	fprintf(stderr, "error: ");
	vfprintf(stderr, fmt, args);
	fprintf(stderr, "\n");
	va_end(args);
	exit(1);
}

void filecopy(int fd1, int fd2) {
	int n;
	char buf[BUFSIZE];

	while((n = read(fd1, buf, BUFSIZE)) > 0)
		if(write(fd2, buf, n) != n)
			error("can't  write to file" );
}

int main(int argc, char* argv[]) {
	int fd;

	if(argc == 0)
		filecopy(0, 1);
	else
		while(--argc > 0) {
			if((fd = open(*++argv, O_RDONLY)) == -1)
				error("can't open file %s", *argv);
			else {
				filecopy(fd, 1);
				close(fd);
			}
		}
}
