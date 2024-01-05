#include<fcntl.h>
#include <unistd.h>
#include "sys/syscall.h"
#include<stdlib.h>

#define PERMS 0666
#define OPEN_MAX 20
#define EOF (-1)
#define BUFSIZE 1024

typedef struct _iobuf {
	int cnt;
	char *ptr;
	char *base;
	struct flag_field {
		unsigned is_read : 1;
		unsigned is_write : 1;
		unsigned is_buf : 1;
		unsigned is_unbuf : 1;
		unsigned is_eof : 1;
		unsigned is_err : 1;		
	} flag;
	int fd;
} FILE;

extern FILE _iob[OPEN_MAX];

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

#define getc(p) (--(p)->cnt >= 0 ? (unsigned char)*(p)->ptr++ : _fillbuf(p))
#define putc(x, p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x), p))

#define getchar() getc(stdin)
#define putchar(x) putc((x), stdout)

int fseek(FILE *fp, long offset, int origin) {
	unsigned nc;
	long rc = 0;

	if(fp -> flag.is_read) {
		if(origin == 1)
			offset -= fp -> cnt;
		rc = lseek(fp -> fd, offset, origin);
		fp -> cnt = 0;
	}
	else if(fp -> flag.is_write) {
		if((nc = fp -> ptr - fp -> base) > 0)
			if(write(fp -> fd, fp -> base, nc) != nc)
				rc = -1;
		if(rc != -1)
			rc = lseek(fp -> fd, offset, origin);
	}

	return (rc == -1) ? -1 : 0;
}

FILE *fopen(char *name, char *mode) {
	int fd;
	FILE *fp;

	if(*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;

	for(fp = _iob; fp < _iob + OPEN_MAX; fp++) {
		if(!fp -> flag.is_read && !fp -> flag.is_write)
			break;
	}

	if(fp >= _iob + OPEN_MAX)
		return NULL;

	if(*mode == 'w')
		fd = creat(name, PERMS);
	else if(*mode == 'a') {
		if((fd = open(name, O_WRONLY, 0)) == -1)
			fd = creat(name, PERMS);
		lseek(fd, 0L, 2);
	}
	else 
		fd = open(name, O_RDONLY, 0);
	if(fd == -1)
		return NULL;
	fp -> fd = fd;
	fp -> cnt = 0;
	fp -> base = NULL;
	fp -> flag.is_unbuf = 0;
	fp -> flag.is_buf = 1;
	fp -> flag.is_eof = 0;
	fp -> flag.is_err = 0;

	if(*mode == 'r') {
		fp -> flag.is_read = 1;
		fp -> flag.is_write = 0;
	}
	else {
		fp -> flag.is_read = 0;
		fp -> flag.is_write = 1;
	}

	return fp;
}

int _fillbuf(FILE *fp) {
	int bufsize;
	if(fp -> flag.is_read == 0 || fp -> flag.is_eof == 1 || fp -> flag.is_err == 1)
		return EOF;
	bufsize = (fp -> flag.is_unbuf == 1) ? 1 : BUFSIZE;
	if(fp -> base == NULL)
		if((fp -> base = (char *) malloc (bufsize)) == NULL)
			return EOF;
	fp -> ptr = fp -> base;
	fp -> cnt = read(fp -> fd, fp -> ptr, bufsize);

	if(--fp -> cnt < 0) {
		if(fp -> cnt == -1)
			fp -> flag.is_eof = 1;
		else
			fp -> flag.is_err = 1;
		fp -> cnt = 0;
		return EOF;
	}

	return (unsigned char) *fp -> ptr++;
}	

int _flushbuf(int c, FILE *f) {
	int num_written, bufsize;
	unsigned char uc = c;

	if(!f -> flag.is_write || f -> flag.is_eof || f -> flag.is_err) {
		return EOF;
	}

	if(f -> base == NULL && !f -> flag.is_unbuf) {
		if((f -> base = malloc(BUFSIZE)) == NULL)
			f -> flag.is_unbuf = 1;
		else {
			f -> ptr = f -> base;
			f -> cnt = BUFSIZE - 1;
		}
	}

	if(f -> flag.is_unbuf) {
		f -> ptr = f -> base = NULL;
		f -> cnt = 0;

		if(c == EOF)
			return EOF;
		
		num_written = write(f -> fd, &uc, 1);
		bufsize = 1;	
	}
	else {
		bufsize = (int) (f -> ptr - f -> base);
		num_written = write(f -> fd, f -> base, bufsize);
		f -> ptr = f -> base;
		f -> cnt = BUFSIZE - 1;
		*f -> ptr++ = (char) c;
	}

	if(num_written == bufsize)
		return c;

	f -> flag.is_err = 1;
	return EOF;
}

int fflush(FILE *f) {
	int retval;
	int i;
	FILE *fp;

	retval = 0;

	if(f == NULL) {
		for(fp = _iob; fp < _iob + OPEN_MAX; fp++)
			if(!fp -> flag.is_write && fflush(fp) == -1)
				retval = -1;
	}
	else {
		if(!f -> flag.is_write)
			return -1;
		_flushbuf(EOF, f);
		if(f -> flag.is_err)
			retval = -1;
	}

	return retval;
}

int fclose(FILE *f) {
	int fd;

	if(f == NULL)
		return -1;

	fd = f -> fd;
	fflush(f);
	f -> cnt = 0;
	f -> ptr = NULL;
	f -> fd = -1;

	return close(fd);
}

FILE _iob[OPEN_MAX] = {
	{0, (char *) 0, (char *)0, {1,0,0,0,0,0}, 0},
	{0, (char *) 0, (char *)0, {0,1,0,0,0,0}, 1},
	{0, (char *) 0, (char *)0, {0,1,0,1,0,0}, 2},
};

int main() {
	FILE *fp = fopen("file1.txt", "r");
        FILE *fp2 = fopen("file.txt", "w");
	int c;
    	
	fseek(fp, 2L, 0);
	while ((c = getc(fp)) != EOF) {
		putc(c, fp2);
    	}
	fclose(fp2);

}
