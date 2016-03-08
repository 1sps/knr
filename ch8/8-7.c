/* Ex 8-7 K&R2 */

/* malloc accepts a size request without checking its plausibility; free
   believes that the block it is asked to free contains a valid size field.
   Improve these routines so they take more pains with error checking.
*/

/* 2016-03-08 Tue 03:39 PM */

#include<stdio.h>
#include<unistd.h>
#include<string.h>

/* use these flags debugging */
#define SKIP
#define DEBUG

/* return status' */
#define MALLOC_ERR 1
#define FREE_ERR   2

typedef long Align;  /* for alignment to long boundary */

/* header structure */
union header {
	struct {
		union header *ptr; /* next block if in free list */
		unsigned size;     /* size of this block */
	} s;
	Align x;      /* force alignment of blocks */
};

typedef union header Header;

static Header base;           /* empty list to get started */
static Header *freep = NULL;  /* start of free list */

/* function prototypes */
void *jmalloc(unsigned nbytes);
Header *jmorecore(unsigned nu);
int jfree(void *ap);
void jpfreelist(Header *hp);

/* main: test jcalloc */
int main(void)
{
	int *p, *q, *r, *s, *t, *ptr, i;
	char *c, *d;

	#ifdef SKIP
	if ((p = jmalloc(sizeof(int))) == NULL)
		return MALLOC_ERR;
	if ((q = jmalloc(sizeof(int))) == NULL)
		return MALLOC_ERR;
	if ((r = jmalloc(sizeof(int))) == NULL)
		return MALLOC_ERR;
	if ((s = jmalloc(sizeof(int))) == NULL)
		return MALLOC_ERR;
	#endif

	if(jfree(q) == 0) 
		return FREE_ERR;
	/* jpfreelist(freep); */

	return 0;
}

#define MAX_BYTES_REQUEST 1000

/* jmalloc: general purpose storage calculator */
void *jmalloc(unsigned nbytes)
{
	Header *p, *prevp;
	Header *jmorecore(unsigned);
	unsigned nunits;

	/* if invalid num of bytes requested */
	if (nbytes < 1 || nbytes > MAX_BYTES_REQUEST)
		return NULL;

	nunits = (nbytes+sizeof(Header)-1)/sizeof(Header) + 1;
	if ((prevp = freep) == NULL) {  /* no free list yet */
		base.s.ptr = freep = prevp = &base;
		base.s.size = 0;
	}
	for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
		if (p->s.size >= nunits) {  /* big enough */
			if (p->s.size == nunits)  /* exactly */
				prevp->s.ptr = p->s.ptr;
			else {                    /* allocate tail end */
				p->s.size -= nunits;
				p += p->s.size;
				p->s.size = nunits;
			}
			freep = prevp;
			return (void *)(p+1);
		}
		if ( p == freep)  /* wrapped around free list */
			if ((p = jmorecore(nunits)) == NULL)
				return NULL;   /* none left */
	}
}

#define NALLOC 1024   /* minimum (#)units to request */

/* morecore: ask system for more memory */
#ifndef SKIP
static Header *jmorecore(unsigned nu)
#endif
/* gcc error for static definition - removing static */
Header *jmorecore(unsigned nu)
{
	#ifndef SKIP
	char *cp, *sbrk(int);
	#endif
	char *cp;
	Header *up;
	int jfree(void *);

	if (nu < NALLOC)
		nu = NALLOC;
	cp = sbrk(nu * sizeof(Header));
	if (cp == (char *) -1)  /* no space at all */
		return NULL;
	up = (Header *) cp;
	up->s.size = nu;
	jfree((void *) (up+1));
	return freep;
}

/* free: put block ap in free list */
int jfree(void *ap)
{
	Header *bp, *p, *testp;

	bp = (Header *)ap - 1;  /* point to block header */
	
	/* check for validity of size */
	if (bp->s.size < 1) /* invalid size */
		return 0;
	testp = bp + bp->s.size;
	for (p=freep->s.ptr; ; p = p->s.ptr) {
		/* if block overlaps (as indicated by size) with existing free block*/
		/* this is also an invalid size */
		if (testp >= p && testp <= p + p->s.size) 
			return 0;
		if (p == freep)
			break;
	}
	/* size validity check done/finished */

	for (p=freep; !(bp > p && bp < p->s.ptr); p=p->s.ptr)
		if (p>=p->s.ptr && (bp > p || bp < p->s.ptr))
			break; /* freed block at start or end of araena */
	
	if (bp + bp->s.size == p->s.ptr) { /* join to upper nbr */
		bp->s.size += p->s.ptr->s.size;
		bp->s.ptr = p->s.ptr->s.ptr;
	} else
		bp->s.ptr = p->s.ptr;
	if (p + p->s.size == bp) {  /* join to lower nbr */
		p->s.size += bp->s.size;
		p->s.ptr = bp->s.ptr;
	} else
		p->s.ptr = bp;
	freep = p;
	return 1;
}

/* jpfreelist: print the free list */
void jpfreelist(Header *hp)
{
	Header *head;
	int i;

	printf("Address of Base: %ld\n", (long) &base);
	for (i=0, head = hp; hp->s.ptr != head; hp = hp->s.ptr, i++ )
		printf("free block: adress = %ld,  num = %d. size = %d\n",
		        (long) hp, i, hp->s.size);
	for (; hp != head; hp = hp->s.ptr, i++)
		printf("free block: adress = %ld,  num = %d. size = %d\n",
		        (long) hp, i, hp->s.size);
}

/* EOF */
