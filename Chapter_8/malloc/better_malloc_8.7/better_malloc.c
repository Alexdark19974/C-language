#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef long Align; /*	для выравнивание по грание long */

union header		/* заголовок блока */
{
	struct
	{
		union header *ptr; /* следующий блок, если есть */
		unsigned int size; /* размер этого блока */
	} s;
	Align x; /* принудительное выравнивание блоков */
};

typedef union header Header;

static Header base = {0};		  /* пустой список для начала */
static Header *freep = NULL;		 /* начало списка */

void *mymalloc(size_t);
void myfree(void *);
static Header *morecore(unsigned int);

int main (int argc, char *argv[])
{
	printf(" Size of Align is %ld\n", sizeof(Align));
    printf(" Size of header is %ld\n", sizeof(Header));
  	printf("Size of struct s is %ld\n", sizeof (base.s));

	char *block_1 = mymalloc(10);

//	myfree(block_1);

	if (block_1 == NULL)
	{
		fprintf(stderr, "error: value is equal to or less than 0\n");
		exit(EXIT_FAILURE);
	}

	char *block_2 = mymalloc(12);

	if (block_2 == NULL)
    {
        fprintf(stderr, "error: value is equal to or less than 0\n");
        exit(EXIT_FAILURE);
    }

//	myfree(block_1);

	char *block_3 = mymalloc(18);

	if (block_3 == NULL)
    {
        fprintf(stderr, "error: value is equal to or less than 0\n");
        exit(EXIT_FAILURE);
    }

	myfree(block_2);

	char *block_4 = mymalloc(100);

	if (block_4 == NULL)
    {
        fprintf(stderr, "error: value is equal to or less than 0\n");
        exit(EXIT_FAILURE);
    }


	char *block_5 = mymalloc(1000);

	if (block_5 == NULL)
    {
        fprintf(stderr, "error: value is equal to or less than 0\n");
        exit(EXIT_FAILURE);
    }



	return 0;
}

/* malloc: функция распределения памяти  */
void *mymalloc(size_t nbytes)
{
	if (nbytes <= 0)
	{
		return NULL;
	}

	Header *p, *prevp;

	// Header *p - a pointer to the current block

	// Header *prevp - a pointer to the previous block

	unsigned int nunits;

	nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1; // calculating the optimal number of units necessary to allocate a requested block.

	/* the bare minimum number of blocks is 2: the 1st is for the Header, the 2nd is for the user */

	prevp = freep; /* prevp points to what freep pointes to */


	if (prevp == NULL)	/* списка ещё нет */
	{
		base.s.ptr = &base; /* base block points to itself     			  */
		freep = &base; 		/* freep points to the base block 			  */
		prevp = &base; 		/* prevp points to the base block 			  */
		base.s.size = 0;	/* sets the size of the base block at 0 bytes */
	}

	for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) /* current block pointer 'p' points to what the field "s.ptr" points to, which is the base block */
	{
		// at the second iteration, "prevp" stores the address of the base block "base", to which the current block pointer 'p' points

		// 'p' now points to the header block of the chunk


		if (p->s.size >= nunits)	/* достаточный размер */ /* at first, s.size is set at 0 */
		{
			// at the second iteration, the size is 1024 which is enough

			if (p->s.size == nunits) 	/* в точности */
			{
				prevp->s.ptr = p->s.ptr;
			}
			else				 /* отрезаем "хвост" */ // since we need to allocated 2 units (Header + the effective space)
			{
				p->s.size -= nunits; /* update the header block of the chunk, since 2 units will be occupied the user request, makes it 1022 */
				p += p->s.size; /* move the current block pointer (happens to be the header block of the chunk) to point to the 1022nd block */
				p->s.size = nunits; /* the 1022nd block stores the requested size which 2 units(the 1022nd and the 1023rd */
			}

				freep = prevp;

			/* freep points to what prevp points to, which is the stored address to base block */

			/* but why? there haven't been any manipulations of freep, have there ?*/

			return p + 1;

			/* returns the allocated space of 16 bytes for the user */
			/* the bundle p + (p + 1) makes a combo of header + space inside of the chunk (header + allocated space), so the chunk is segmented. )*/
		}

		if (p == freep) /* if current block pointer points to what freep points to, then we have no memory allocated */
		{
			p = morecore(nunits); /* allocates a chunk of memory */

			/* p now points to what freep points to, which is the header of the chunk */

			if (p == NULL)
			{
				return NULL; 	/* не осталось памяти */
			}
		}
	}
}

#define NALLOC 1024 /* минимально запрашиваемое количество блоков */

/* morecore: запрос дополнительной памяти у системы */

static Header *morecore (unsigned int nu)
{
	char *cp; /* pointer to a chunk of memory */
	Header *up; /* pointer to the upper-most block of memory allocated */

	if (nu < NALLOC)
	{
		nu = NALLOC; /* nu is 2, but the first allocation should be much higher than that, so there are 1024 units allocated (hence the chunk) */
	}

	cp = sbrk(nu * sizeof(Header)); /* allocates 1024 * 16 = 16384 bytes of memory for 1024 units/blocks */

	if (cp == (char *) -1)	/* места в памяти нет */
	{
		return NULL;
	}

	up = (Header *) cp; // up points to the base address of the chunk, and views it as a number of blocks (units)
	up->s.size = nu; /* sets the size of up as 1024 */

	/* up becomes the header block of the allocated chunk */

	myfree(up + 1);

	/* "myfree" doesn't free the allocated memory, but initializes the circular free list */

	/* up + 1 is a hint that the work will be done starting at the 1st block after the header of the chunk */

	return freep; // returns the updated pointer to the block in a free list, the field s.ptr points to the header of the chunk.
}

/* free: помещение блока ap в список свободных блоков */
void myfree (void *ap)
{
	if (ap == NULL)
	{
		fprintf(stderr, "error: can't free NULL pointer.\n");
		exit(EXIT_FAILURE);
	}

	Header *bp, *p;

	/* bp is a base pointer that points to the header of the chunk */

	/* p is a current pointer that points to a block of the chunk */

	bp = (Header *) ap - 1; /*  указатель на заголовок */

	/* bp now points to the header of the chunk */

	if (bp->s.size = 0)
	{
		fprintf("error: can't free the block with size of 0.\n");
		exit(EXIT_FAILURE);
	}

	for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr) // the current block pointer 'p' points to what freep points to, which is the base block of the free list "base"
	{
		if ((p >= p->s.ptr) && (bp > p || bp < p->s.ptr)) /* at first,  p == p->s.ptr since they point to the base block "base", bp is greater than p by default */
		{
			break; /* освобождаемый блок в начале или в конце */
		}
	}

	if (bp + bp->s.size == p->s.ptr)	/* к верхнему соседу */
	{
		bp->s.size += p->s.ptr->s.size;
		bp->s.ptr = p->s.ptr->s.ptr;
	}
	else
	{
		bp->s.ptr = p->s.ptr; /* the field s.ptr of bp points to the base block "base", which becomes chained to the base block "base" */

		// the header of the chunk now nows the address of the base block "base"
	}
	if (p + p->s.size == bp)
	{
		p->s.size += bp->s.size;		/* к нижнему соседу */
		p->s.ptr = bp->s.ptr;
	}
	else
	{
		p->s.ptr = bp; // the current block pointer now points to the header of the chunk

		/* the base block is chained to the header of the chunk, the header of the chunk is chained to the base block, thus the word "circular" free list */
	}

	freep = p; /* pointer to the block in a free list now points to what p points to with the previous modifications, freep points to the block in the free list */

	/* which doesn't really change thigns since the line "p->s.ptr = bp" has already done the job ?! */

	/* freep and p are identical at that point, so why "freep = p" ?! */
}

