/* Ex 8-3 KNR2 */
/*
   Design and write _flushbuf, fflush, and fclose.
*/
/* 2016-03-04 Fri 02:34 AM */

#define NULL 0
#define EOF (-1)
#define BUFSIZE 1024
#define OPEN_MAX 20  /* maximum number of open files */
#define DEBUG1

/* for debugging */
int printf(const char *, ...);

/* FILE structure */
typedef struct _iobuf {
	int cnt;      /* num of char left */
	char *ptr;    /* pointer to next char */
	char *base;   /* pointer to the buffer */
	int flag;     /* mode of file access */
	int fd;       /* file descriptor */
} FILE;

extern FILE _jiob[OPEN_MAX];

#define stdin (&_jiob[0])
#define stdout (&_jiob[1])
#define stderr (&_jiob[2])

enum _flags {
	_READ = 01,   /* file open in read mode */
	_WRITE = 02,  /* file open in write mode*/
	_UNBUF = 04,  /* file to be unbuffered */
	_EOF = 010,    /* EOF has occured */
	_ERR = 020     /* Error has occured */
};

int _jfilbuf(FILE *);
int _jflushbuf(unsigned int, FILE *);

#define jfeof(p) (((p)->flag & _EOF) != 0)
#define jferror(p) (((p)->flag & _ERR) != 0)
#define jfileno(p) ((p)->fd)

#define jgetc(p) (--(p)->cnt >= 0 \
                ? (unsigned char) *(p)->ptr++ : _jfillbuf(p))
#define jputc(x, p)  (--(p)->cnt >= 0 \
                ? *(p)->ptr++ = (x) : _jflushbuf((x), p))

#define jgetchar() jgetc(stdin)
#define jputchar(x) jputc(x, stdout)

/* --- */
/* #include<syscalls.h> */
/* --- */
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>

#define PERMS 0666

int jfclose(FILE *);

/* jfflush: flush buf of write files */
void jfflush(FILE *fp)
{
	int cnt, bufsize;
	
	printf("jfflush called\n");
	bufsize = (fp->flag & _UNBUF ? 1 : BUFSIZE);
	if ((cnt = write(fp->fd, fp->base, bufsize - fp->cnt)) != bufsize -
	     fp->cnt) {
		printf("cnt -ne fp->cnt\n");
		return ;
	}
	else {
		fp->cnt = bufsize;
		fp->ptr = fp->base;
		fp->cnt--;
	}
}

/* jfclose: close an opened file */
int jfclose(FILE *fp)
{
	int c, cnt, bufsize;

	/* if write open, flush the buf into the file*/
	if (fp->flag & _WRITE)
		if (fp->ptr != fp->base)
			jfflush(fp);
	/* Reset counters */
	fp->cnt = 0;
	fp->ptr = NULL;
	/* Free memory */
	free(fp->base); 
	fp->base = NULL;
	if ((c = close(fp->fd)) == -1)
		return -1;
	else {
		fp->flag |= 0;
		return c;
	}
}

/* fopen: open file, return file pointer */
FILE *jfopen(char *name, char *mode)
{
	int fd;
	FILE *fp;

	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;
	for (fp = _jiob; fp < _jiob + OPEN_MAX; fp++)
		if ((fp->flag & (_READ | _WRITE)) == 0)
			break;    /* found free slot */
	if (fp == _jiob + OPEN_MAX)
		return NULL;
	
	if (*mode == 'w')
		fd = creat(name, PERMS);
	else if (*mode == 'a') {
		if ((fd = open(name, O_WRONLY, 0)) == -1)
			fd = creat(name, PERMS);
		lseek(fd, 0L, 2);
	}
	else if (*mode == 'r')
		fd = open(name, O_RDONLY, 0);
	
	if (fd == -1)
		return NULL;
	
	fp->fd = fd;
	fp->cnt = 0;
	fp->base = NULL;
	fp->flag = (*mode == 'r') ? _READ : _WRITE;
	fp->flag |= _UNBUF; 
	return fp;
}

/* --- */
/* #include<syscalls.h> */
/* --- */

/* _fillbuf: allocate and fill input buffer */
int _jfillbuf(FILE *fp)
{
	int bufsize;

	if ((fp->flag & (_READ | _EOF | _ERR)) != _READ) {
		printf("_jfillbuf: returning EOF: NOT READ\n");
		return EOF;
	}
	bufsize = ((fp->flag & _UNBUF) ? 1 : BUFSIZE);

	if (fp->base == NULL)
		if ((fp->base = (char *) malloc(bufsize)) == NULL)
			return EOF;
	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->base, bufsize);
	if (--fp->cnt < 0) {
		if (fp->cnt == -1)
			fp->flag |= _EOF;
		else
			fp->flag |= _ERR;
		fp->cnt = 0;
		return EOF;
	}
	return (unsigned char) *fp->ptr++;
}

/* _jflushbuf: flush write buffer */
int _jflushbuf(unsigned int x, FILE *fp)
{
	int bufsize, cnt;
	char nlbuf[1];

	if ((fp->flag & (_WRITE | _EOF | _ERR)) != _WRITE)
		return EOF;

	if (fp->base == NULL) {
		bufsize = ((fp->flag & _UNBUF) ? 1 : BUFSIZE);
		printf("_jflushbuff: bufsize: %d\n", bufsize);
		if ((fp->base = (char *) malloc(bufsize)) == NULL)
			return EOF;
		fp->ptr = fp->base;
		*fp->ptr++ = x;
		fp->cnt = bufsize;
		fp->cnt--;
	} else {
		if ((cnt = write(fp->fd, fp->base, bufsize - fp->cnt - 1)) != bufsize -
		fp->cnt - 1)
			return EOF;
		else {
			fp->cnt = bufsize;
			fp->ptr = fp->base;
			*fp->ptr++ = x;
			fp->cnt--;
		}
	}
	return (unsigned char) x;
}

FILE _jiob[OPEN_MAX] = {
					  	{0, (char *) 0, (char *) 0, _READ, 0},
					  	/* {0, (char *) 0, (char *) 0, _WRITE , 1}, */
					  	{0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 1},
					  	{0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2}
					 };


int main(int argc, char *argv[]) /* test stdio implementation */
{
	int c, i;
	FILE *fp1, *fp2;

	if (argc != 3)
		return ((!printf("Ex 8-3: syntax error\n ")) + 1);

	if ((fp1 = jfopen(argv[1], "r")) == NULL)
		return ((!printf("Ex 8-3: can't open %s\n ", argv[1])) + 1);
		
	if ((fp2 = jfopen(argv[2], "w")) == NULL)
		return ((!printf("Ex 8-3: can't open %s\n ", argv[2])) + 1);

	 while ((c = jgetc(fp1)) != EOF)  
	    jputc(c, fp2);

	if ((c = jfclose(fp1)) == -1) {
		printf("error: could not close file\n"); 
		return 1;
	}
	if ((c = jfclose(fp2)) == -1) {
		printf("error: could not close file\n"); 
		return 1;
	}
	return 0;
}

/* EOF */
