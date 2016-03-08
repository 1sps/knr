/* KNR2 Ex 8-2  */
/* 
   Rewrite fopen and _fillbuf with fields instead of explicit bit operations.
   Compare code size and execution speed.
*/
/* 2016-03-02 Wed 09:41 PM */

#define NULL
#define EOF (-1)
#define BUFSIZE 1024
#define OPEN_MAX 20  /* maximum number of open files */

/* just for debugging */
int printf(const char *, ...);

typedef struct _iobuf
{
	int cnt;      /* num of char left */
	char *ptr;    /* pointer to next char */
	char *base;   /* pointer to the buffer */
	#ifdef SKIP
	int flag;     /* mode of file access */
	#endif
	struct        /* fields for all flags */
	{             /* of file access*/
		unsigned int field_read : 1;
		unsigned int field_write : 1;
		unsigned int field_unbuf : 1;
		unsigned int field_eof : 1;
		unsigned int field_err : 1;
	} flag; 
	int fd;       /* file descriptor */
} FILE;

extern FILE _jiob[OPEN_MAX];

#define stdin (&_jiob[0])
#define stdout (&_jiob[1])
#define stderr (&_jiob[2])

enum _flags
{
	_READ = 01,   /* file open in read mode */
	_WRITE = 02,  /* file open in write mode*/
	_UNBUF = 04,  /* file to be unbuffered */
	_EOF = 010,    /* EOF has occured */
	_ERR = 020     /* Error has occured */
};

int _jfilbuf(FILE *);
int _jflushbuf(int, FILE *);

#define jfeof(p) (((p)->flag & _EOF) != 0)
#define jferror(p) (((p)->flag & _ERR) != 0)
#define jfileno(p) ((p)->fd)

#define jgetc(p) (--(p)->cnt >= 0 \
                ? (unsigned char) *(p)->ptr++ : _jfillbuf(p))
#define jputc(x, p)  (--(p)->cnt >= 0 \
                ? *(p)->ptr++ = x : _jflushbuf(x, p))

#define jgetchar() jgetc(stdin)
#define jputchar(x) jputc(x, stdout)

#include<fcntl.h>
/* #include<syscalls.h> */
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

#define PERMS 0666

/* fopen: open file, return file pointer */
FILE *jfopen(char *name, char *mode)
{
	int fd;
	FILE *fp;

	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;
	for (fp = _jiob; fp < _jiob + OPEN_MAX; fp++)
		/* if ((fp->flag & (_READ | _WRITE)) == 0) */
		if (fp->flag.field_read == 0 || fp->flag.field_write == 0)
			break;    /* found free slot */
	if (fp == _jiob + OPEN_MAX)
		return NULL;
	
	if (*mode == 'w')
		fd = creat(name, PERMS);
	else if (*mode == 'a')
	{
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
	/* fp->flag = (*mode == 'r') ? _READ : _WRITE; */
	if (*mode == 'r')
	{
		fp->flag.field_read = 1;
		fp->flag.field_write = 0;
	}
	else if (*mode == 'w')
	{
		fp->flag.field_write = 1;
		fp->flag.field_read = 0;
	}
	/* fp->flag = (*mode == 'r') ? _READ : _WRITE; */
	return fp;
}

/* #include<syscalls.h> */

#include<stdlib.h>

/* _fillbuf: allocate and fill input buffer */
int _jfillbuf(FILE *fp)
{
	int bufsize;

	#ifdef DEBUG
	printf("_jfillbuf called\n");
	printf("fd: %d\n", fp->fd);
	printf("flag: %d\n", fp->flag);
	#endif
	/* if ((fp->flag & (_READ | _EOF | _ERR)) != _READ) */
	if (fp->flag.field_read != 1)
	{
		#ifdef DEBUG
		printf("_jfillbuf: returning EOF: NOT READ\n");
		#endif
		return EOF;
	}
	/* bufsize = (fp->flag & _UNBUF ? 1 : BUFSIZE); */
	if (fp->flag.field_unbuf == 1)
		bufsize = 1;
	else
		bufsize = BUFSIZE;

	if (fp->base == NULL)
		if ((fp->base = (char *) malloc(bufsize)) == NULL)
			return EOF;
	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->base, bufsize);
	if (--fp->cnt < 0)
	{
		if (fp->cnt == -1)
			/* fp->flag |= _EOF; */
			fp->flag.field_eof = 1;
		else
			fp->flag.field_err = 1;
			/* fp->flag |= _ERR; */
		fp->cnt = 0;
		return EOF;
	}
	#ifdef DEBUG
	printf("buf_base: %s\n", fp->base);
	#endif
	return (unsigned char) *fp->ptr++;
}

FILE _jiob[OPEN_MAX] = {
					  	{0, (char *) 0, (char *) 0, _READ, 0},
					  	{0, (char *) 0, (char *) 0, _WRITE, 1},
					  	{0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2}
					 };


int main(void) /* test jfopen() jfgetc() */
{
	
	FILE *fp = jfopen("test", "r");
	int c;
	
	#ifdef DEBUG
	printf("stdin fd: %d\n", stdin->fd);
	#endif
	while ((c = jgetc(fp)) != EOF)
		printf("%c", c);

	return 0;
}

/* EOF */
