#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/syscall.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/dir.h>
#include "dirent.h"

#define MAXPATH 1024
#define MAXNAME 14
#ifndef DIRSIZ
#define DIRSIZ 14
#endif

typedef struct {
	long ino;
	char name[MAXNAME + 1];
} Dirent;

typedef struct {
	int fd;
	Dirent d;
} DIRE;	

DIRE *opendirect(char *name) {
	int fd;
	struct stat stbuf;
	DIRE *dp;

	if((fd = open(name, O_RDONLY, 0)) == -1 || fstat(fd, &stbuf) == -1 || (stbuf.st_mode & S_IFMT) != S_IFDIR || (dp = (DIRE *) malloc(sizeof(DIRE))) == NULL)
		return NULL;
	dp -> fd = fd;
	return dp;
}	

void closedirect(DIRE *dp) {
	if(dp) {
		close(dp -> fd);
		free(dp);
	}
}

Dirent *readdirect(DIRE *dp) {
	struct direct dirbuf;
	static Dirent d;

	while(read(dp -> fd, (char *) &dirbuf, sizeof(dirbuf)) == sizeof(dirbuf)) {
		if(dirbuf.d_ino == 0)
			continue;
		d.ino = dirbuf.d_ino;
		strncpy(d.name, dirbuf.d_name, DIRSIZ);
		d.name[DIRSIZ] = '\0';
		return &d;
	}

	return NULL;
}

void dirwalk(char *dir, void (*fcn)(char *)) {
	char name[MAXPATH];
	Dirent *dp;
	DIRE *dfd;

	if((dfd = opendirect(dir)) == NULL) {
		fprintf(stderr, "can't open %s\n", dir);
		return;
	}

	while((dp = readdirect(dfd)) != NULL) {
		if(strcmp(dp -> name, ".") == 0 || strcmp(dp -> name, "..") == 0)
			continue;
		if(strlen(dir) + strlen(dp -> name) + 2 > sizeof(name)) {
			fprintf(stderr, "dirwalk: name %s %s too long.\n", dir, dp -> name);
			return;
		}
		sprintf(name, "%s %s", dir, dp -> name);
		(*fcn)(name);
	}

	closedirect(dfd);
}		

void fsize(char *name) {
	struct stat stbuf;

	if(stat(name, &stbuf) == -1) {
		fprintf(stderr, "can't acces %s\n", name);
		return;
	}

	if((stbuf.st_mode & S_IFMT) == S_IFDIR)
		dirwalk(name, fsize);

	printf("%5lu %6o %3lu %8ld %s", stbuf.st_ino, stbuf.st_mode, stbuf.st_nlink, stbuf.st_size, name);
}

int main(int argc, char *argv[]) {
	if(argc == 1)
		fsize(".");
	else
		while(--argc > 0)
			fsize(*++argv);
	return 0;
}
