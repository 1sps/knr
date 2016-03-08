/* Ex 8-1 K&R2 */

/* Write cat using system calls */

/* 2016-02-28 Sun 04:23 AM */

#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

/* cat: concatenate files version 2 */

int main(int argc, char *argv[])
{
	FILE *fp;
	int fd;
	void filecopy(int, int);
	char *prog = argv[0];  /* program name for errors */

	if (argc == 1) /* no args; copy standard input */
		filecopy(0, 1);
	else
		while (--argc > 0)
			if ((fd = open(*++argv, O_RDONLY, 0)) == -1)
			{
				fprintf(stderr, "%s: can't open %s\n", 
				    prog, *argv);
				exit(1);
			} else
			{
				filecopy(fd, 1);
				close(fd);
			}
	exit(0);
}

/* filecopy: copy file ifp to file ofp */
void filecopy(int fd1, int fd2)
{
	int n;
	char c;

	while ((n = read(fd1, &c, 1)) != 0 && n == 1)
		if ((n = write(fd2, &c, 1)) != 1)
			fprintf(stderr, "filecopyi: error while copying\n");
}
/* EOF */
