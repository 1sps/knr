/* Ex 8-6 K&R2 */

/* The standard library function calloc(n, size) returns a pointer to n objects
   of size 'size', with the storage initialized to zero. Write calloc, by
   calling malloc or by modifying it.
*/

/* 2016-03-08 Tue 03:39 PM */

#include<stdio.h>
#include<unistd.h>
#include<string.h>

/* use these flags debugging */
#define SKIP
#define DEBUG

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
void *jcalloc(unsigned size);
void *jcalloc2(unsigned size);
void *jmalloc(unsigned nbytes);
Header *jmorecore(unsigned nu);
void jfree(void *ap);
void jpfreelist(Header *hp);

/* main: test jcalloc */
int main(void)
{
	int *p, *q, *r, *s, *t, *ptr, i;
	char *c, *d;

	p = jmalloc(sizeof(int));
	q = jmalloc(sizeof(int));
	r = jmalloc(sizeof(int));
	s = jmalloc(sizeof(int));

	jfree(q);
	/* jpfreelist(freep); */

	t = jcalloc(10 * sizeof(int));
	/* verify zero initialized */
	printf("jcalloc returned storage:\n");
	for (ptr = t, i=0; i<10; i++, ptr++)
		printf("%d ", *ptr);
	putchar('\n');
	jfree(t);

	t = jcalloc2(10 * sizeof(int));
	/* verify zero initialized */
	printf("jcalloc2 returned storage:\n");
	for (ptr = t, i=0; i<10; i++, ptr++)
		printf("%d ", *ptr);
	putchar('\n');
	jfree(t);

	return 0;
}

/* jcalloc: allocate storage initialized to zero */
void *jcalloc(unsigned size)
{
	char *cp, *ptr;

	cp = jmalloc(size);
	for (ptr = cp; --size > 0; ptr++)  /* initialize to zero */
		*ptr = 0;
	return cp;
}

/* jcalloc2: allocate storage initialized to zero */
/* jcalloc2: no call to malloc */
void *jcalloc2(unsigned size)
{
	Header *p, *prevp;
	Header *jmorecore(unsigned);
	unsigned nunits;
	char *cp;
	int i;

	nunits = (size+sizeof(Header)-1)/sizeof(Header) + 1;
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
			cp = (char *) (p + 1);
			/* initialize to zero */
			for (i=0; i < p->s.size * sizeof(Header); i++)
				*cp++ = 0;

			return (void *)(p+1);
		}
		if ( p == freep)  /* wrapped around free list */
			if ((p = jmorecore(nunits)) == NULL)
				return NULL;   /* none left */
	}
}

/* jmalloc: general purpose storage calculator */
void *jmalloc(unsigned nbytes)
{
	Header *p, *prevp;
	Header *jmorecore(unsigned);
	unsigned nunits;

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
	void jfree(void *);

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
void jfree(void *ap)
{
	Header *bp, *p;

	bp = (Header *)ap - 1;  /* point to block header */
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
