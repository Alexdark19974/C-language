#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef long Align; /*  для выравнивание по грание long */

union header        /* заголовок блока */
{
    struct
    {
        union header *ptr; /* следующий блок, если есть */
        unsigned int size; /* размер этого блока */
    } s;
    Align x; /* принудительное выравнивание блоков */
};

typedef union header Header;

static Header base = {0};         /* пустой список для начала */
static Header *freep = NULL;         /* начало списка */

void *mycalloc(size_t, size_t);
void myfree(void *);
void bfree(void *, size_t);

static Header *morecore(unsigned int);

int main (int argc, char *argv[])
{
   /*

	printf(" Size of Align is %ld\n", sizeof(Align));
    printf(" Size of header is %ld\n", sizeof(Header));
    printf(" Size of struct s is %ld\n", sizeof (base.s));

   */

    char *block_1 = mycalloc(1, sizeof(Header));

	if (block_1 == NULL)
	{
		fprintf(stderr, "error: NULL pointer.\n");
		exit(EXIT_FAILURE);
	}

    char *block_2 = mycalloc(1, sizeof(Header));

	if (block_2 == NULL)
    {
        fprintf(stderr, "error: NULL pointer.\n");
        exit(EXIT_FAILURE);
    }

    char *block_3 = mycalloc(1, sizeof(Header));

	if (block_3 == NULL)
    {
        fprintf(stderr, "error: NULL pointer.\n");
        exit(EXIT_FAILURE);
    }

	myfree(block_1);

	bfree(block_2, sizeof(Header) + sizeof(Header));

	char *block_4 = mycalloc(1, sizeof(Header));

	if (block_4 == NULL)
    {
        fprintf(stderr, "error: NULL pointer.\n");
        exit(EXIT_FAILURE);
    }

	char *block_5 = mycalloc(1, sizeof(Header));

	if (block_5 == NULL)
    {
        fprintf(stderr, "error: NULL pointer.\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}


/* malloc: функция распределения памяти  */
void *mycalloc(size_t nmemb, size_t size)
{
	if (nmemb < 1)
	{
		fprintf(stderr, "error: can't allocate memory for value less than or equal to 0.\n");
		exit(EXIT_FAILURE);
	}

	size_t nbytes = nmemb * size;

    Header *p, *prevp;

    unsigned int nunits;

    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;

    prevp = freep;

    if (prevp == NULL)  /* списка ещё нет */
    {
        base.s.ptr = &base;
        freep = &base;
        prevp = &base;
        base.s.size = 0;
    }

    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr)
    {
        if (p->s.size >= nunits)    /* достаточный размер */
        {
            if (p->s.size == nunits)    /* в точности */
            {
                prevp->s.ptr = p->s.ptr;
            }
            else                 /* отрезаем "хвост" */
            {
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }

            freep = prevp;

            return p + 1;
        }

        if (p == freep)
        {
            p = morecore(nunits);

            if (p == NULL)
            {
                return NULL;    /* не осталось памяти */
            }
        }
    }
}

#define NALLOC 1024 /* минимально запрашиваемое количество блоков */

/* morecore: запрос дополнительной памяти у системы */

static Header *morecore (unsigned int nu)
{
    char *cp;
    Header *up;

    if (nu < NALLOC)
    {
        nu = NALLOC;
    }

    cp = sbrk(nu * sizeof(Header));

    if (cp == (char *) -1)  /* места в памяти нет */
    {
        return NULL;
    }

    up = (Header *) cp;

	Header *temp_up = up;

	for (int i = sizeof(Header); i <= nu && (i < (nu * sizeof(Header))); i+=sizeof(Header))
    {
		temp_up->s.ptr = NULL;
		temp_up->s.size = 0;
		temp_up+=sizeof(Header);
    }

    up->s.size = nu;

    myfree(up + 1);

    return freep;
}

/* free: помещение блока ap в список свободных блоков */
void myfree (void *ap)
{
	if (ap == NULL)
	{
		fprintf(stderr, "error, can't do double free.\n");
		exit(EXIT_FAILURE);
	}

    Header *bp, *p;

    bp = (Header *) ap - 1; /*  указатель на заголовок */

    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
    {
        if ((p >= p->s.ptr) && (bp > p || bp < p->s.ptr))
        {
            break; /* освобождаемый блок в начале или в конце */
        }
    }

    if (bp + bp->s.size == p->s.ptr)    /* к верхнему соседу */
    {
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    }
    else
    {
        bp->s.ptr = p->s.ptr;
    }
    if (p + p->s.size == bp)
    {
        p->s.size += bp->s.size;        /* к нижнему соседу */
        p->s.ptr = bp->s.ptr;
    }
    else
    {
        p->s.ptr = bp;
    }

    freep = p;
}

void bfree(void *p, size_t n)
{
	if (n < (sizeof(Header) + sizeof(Header)))
	{
		fprintf(stderr, "error: an arbitrary block can't be of size less than 32 bytes or less than 2 blocks.\n");
		exit(EXIT_FAILURE);
	}

	if (p == NULL)
	{
		fprintf(stderr, "error: can't free NULL pointer.\n");
		exit(EXIT_FAILURE);
	}

	if (freep == NULL)
	{
		freep = &base;
		base.s.ptr = &base;
		base.s.size = 0;
		return;
	}

	Header *bp;

	bp = (Header *) p;

	bp->s.size = n / sizeof(Header);

	myfree(bp + 1);
}
