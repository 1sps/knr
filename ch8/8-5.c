/* Ex 8-5 KNR2 */
/*
   Modify the fsize program tp print the other information contained in the inode
   directory
*/
/* readdir as is given in K&R2 is given for system V unix and has issues while running
   in GNU/Linux.
   http://www.verycomputer.com/174_f662a819800b8710_1.htm
*/
/* 2016-03-05 Sat 09:58 PM */

#include<stdio.h>
#include<string.h>
/* #include"syscalls.h" */
#include<fcntl.h>      /* flags for read and write */
#include<sys/types.h>  /* typedefs */
#include<sys/stat.h>   /* structures returned by stat */
#include"jdirent.h"
#include<stdlib.h>
#include<unistd.h>

void jfsize(char *);
void printinfo(struct stat stbuf, char *name);

/* print file sizes */
int main(int argc, char **argv)
{
	if (argc == 1)
		jfsize(".");  /* default current directory */
	else
		while (--argc > 0 )
			jfsize(*++argv);
	return 0;
}
/* included sys/stat for declaration */
/* int stat(char *, struct stat *); */
void jdirwalk(char *, void (*fcn)(char *));

/* fsize: print size of file "name" */
void jfsize(char *name)
{
	struct stat stbuf;

	if (stat(name, &stbuf) == -1) {
		fprintf(stderr, "fsize: can't access %s\n", name);
		return;
	}
	if ((stbuf.st_mode & S_IFMT) == S_IFDIR){
		jdirwalk(name, jfsize);
	}
	printinfo(stbuf, name); /* print the info */
	/* printf("%8ld %s\n", stbuf.st_size, name); */
}

/* printinfo: print the info of file */
void printinfo(struct stat stbuf, char *name)
{
	/* Minimal one */
	/* Just demonstrates that different propertie of a file can be found in the
	   stat structure. However to print them nicely (like `ls') other library
	   routines should be used. 
	*/
	printf("%d %d %8ld %s\n",
	       stbuf.st_uid, stbuf.st_gid, stbuf.st_size, name);
}
#define jMAX_PATH 1024

/* dirwalk: apply fcn to all files in directory */
void jdirwalk(char *dir, void (*fcn)(char *))
{
	char name[jMAX_PATH];
	jDirent *dp;
	jDIR *dfd;

	if ((dfd = jopendir(dir)) == NULL) {
		fprintf(stderr, "dirwalk: can't open %s\n", dir);
		return;
	}
	while ((dp = jreaddir(dfd)) != NULL) {
		if (strcmp(dp->name, ".") == 0 
		    || strcmp(dp->name, "..") == 0)
				continue;  /* skip self and parent */
		if (strlen(dir)+strlen(dp->name)+2 > sizeof(name))
			fprintf(stderr, "dirwalk: name %s %s too long\n", 
			         dir, dp->name);
		else {
			sprintf(name, "%s/%s", dir, dp->name);
			(*fcn)(name);
		}
	}
	jclosedir(dfd);
}

#ifndef jDIRSIZE
#define jDIRSIZE 14
#endif
struct direct {
	ino_t d_ino;           /* inode number */
	char d_name[jDIRSIZE]; /* long name does not have '\0' */
};

int fstat(int fd, struct stat *);

/* opendir: open a directory for readdir calls */
jDIR *jopendir(char *dirname)
{
	int fd;
	struct stat stbuf;
	jDIR *dp;

	if ((fd = open(dirname, O_RDONLY, 0)) == -1 
	     || fstat(fd, &stbuf) == -1
		 || (stbuf.st_mode & S_IFMT) != S_IFDIR
		 || (dp = (jDIR *) malloc(sizeof(jDIR))) == NULL)
		 	return NULL;
	dp->fd = fd;
	return dp;
}

/* closedir: close directory opened by opendir */
void jclosedir(jDIR *dp)
{
	if (dp) {
		close(dp->fd);
		free(dp);
	}
}

#include<sys/dir.h>

/* readdir: read directory entries in sequence */
jDirent *jreaddir(jDIR *dp)
{
	struct direct dirbuf;
	static jDirent d;
	int cnt;

	while ((cnt = read(dp->fd, (char *) &dirbuf, sizeof(dirbuf)))
	        == sizeof(dirbuf)) {
		printf("readdir: should not return null");
		if (dirbuf.d_ino == 0)	   /* slot not in use */
			continue;
		d.ino = dirbuf.d_ino;
		strncpy(d.name, dirbuf.d_name, jDIRSIZE);
		d.name[jDIRSIZE] = '\0';
		return &d;
	}
	return NULL;
}

/* EOF */
