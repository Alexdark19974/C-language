#include "syscalls.h"

static union Header base;         /* empty list to get started */
static union Header *freep = NULL;        /* start of free list */
static union Header *morecore(unsigned);

main (void)
{
    start_client_database();
    return 0;
}

/* malloc: general-purpose storage allocator */
void *_malloc(unsigned nbytes)
{
    union Header *p, *prevp;
    union Header *morecore(unsigned);
    unsigned nunits;

    nunits = (nbytes + sizeof(union Header) - 1) / sizeof(union Header) + 1; // 1 nunit == 16 bytes

    if (nunits <= 1) {
        fprintf(stderr, "[%s:%s:%d] error: cannot allocated block size of %u (too small)!\n", __FILE__, __FUNCTION__, __LINE__, nbytes);
        return NULL;
    }

    if ((prevp = freep) == NULL) {  /* no free list yet */
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }
    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) { // prevp is necessary to remember the position for freep before doing p = p->s.ptr;
        if (p->s.size >= nunits) {      /* big enough */
            if (p->s.size == nunits)     /* exactly */
                prevp->s.ptr = p->s.ptr;
            else {              /* allocate tail end */
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *)(p + 1);
        }
        if (p == freep)     /* wrapped around free list */
            if ((p = morecore(nunits)) == NULL)
                return NULL;    /* none left */
    }
}

/* calloc: general-purpose storage allocator setting nbytes to zero */
void *_calloc(unsigned nmemb, unsigned nbytes)
{
    union Header *p, *prevp;
    union Header *morecore(unsigned);
    unsigned nunits;

    nunits = ((nbytes + sizeof(union Header) - 1) / sizeof(union Header) + 1) * nmemb; // 1 nunit == 16 bytes

    if (nunits <= 1) {
        fprintf(stderr, "[%s:%s:%d] error: cannot allocated block size of %u! (too small)\n", __FILE__, __FUNCTION__, __LINE__, nmemb * nbytes);
        return NULL;
    }

    if ((prevp = freep) == NULL) {  /* no free list yet */
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }
    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) { // prevp is necessary to remember the position for freep before doing p = p->s.ptr;
        if (p->s.size >= nunits) {      /* big enough */
            if (p->s.size == nunits)     /* exactly */
                prevp->s.ptr = p->s.ptr;
            else {              /* allocate tail end */
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
                memset(p + 1, 0, nbytes);
            }
            freep = prevp;
            return (void *)(p + 1);
        }
        if (p == freep)     /* wrapped around free list */
            if ((p = morecore(nunits)) == NULL)
                return NULL;    /* none left */
    }
}

#define NALLOC  1024     /* minimum #units to request */

/* morecore: ask system for more memory */
static union Header *morecore(unsigned nu)
{
    char *cp, *_sbrk(int);
    union Header *up;

    if (nu < NALLOC)
        nu = NALLOC;
    cp = sbrk(nu * sizeof(union Header));
    if (cp == (char *) -1) /* no space at all */
        return NULL;
    up = (union Header *) cp;
    up->s.size = nu;
    _free((void *)(up + 1));
    return freep;
}

/* free:  put block ap in free list */
void _free(void *ap)
{
    union Header *bp, *p;

    bp = (union Header *) ap - 1;       /* point to block header */
    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr) {
        if (p != &base && !p->s.size) {
            fprintf(stderr, "[%s:%s:%d] error: allocated block size is zero!\n", __FILE__, __FUNCTION__, __LINE__);
            freep = NULL;
            return;
        }
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break;      /* freed block at start or end of arena */
    }
    if (bp + bp->s.size == p->s.ptr) {  /* join to upper nbr */
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    } else
        bp->s.ptr = p->s.ptr;
    if (p + p->s.size == bp) {          /* join to lower nbr */
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } else
        p->s.ptr = bp;
    freep = p;
}

void display_freelist(void)
{
    union Header *p;

    p = freep;

    do {
        printf("block=%p", (void *) p);
        printf(p == &base ? freep == &base ? "(base, freep);\n" : "(base);\n" : p == freep ? "(freep);\n" : ";\n");
        printf("block size =%u;\n", p->s.size);
        printf("next block=%p", (void *) p->s.ptr);
        printf(p->s.ptr == &base ? freep == &base ? "(base, freep);\n" : "(base);\n" : p->s.ptr== freep ? "(freep);\n" : ";\n");
        p = p->s.ptr;

    } while (p != freep);
}

// p.s : NEVER use free() on brk / sbrk()
void free_all(struct Client *head)
{
    if (head == NULL)
        return;
    free_all(head->next);
    _free(head);
}

void unsbrk(void)
{
    if (sbrk(base.s.ptr->s.size * (-1)) == (char *) -1)
            fprintf(stderr, "error freeing memory from sbrk()\n");
}

/* bfree: free an arbitary block 'p' of 'n' characters to the freelist */
int bfree(void *p, unsigned int n)
{
    if (!n || !p || n < sizeof(union Header)) {
        fprintf(stderr, "error: incorrect input data (null pointer or n is less than 1 unit (= %ld))", sizeof(union Header));
        return -1;
    }

    union Header *bp;

    bp = (union Header *) p;
    /* do the same what we did in _malloc() / _calloc() */
    bp->s.size = (n + sizeof(union Header) - 1) / sizeof(union Header) + 1; // 1 nunit == 16 bytes
    _free(bp + 1);

    return 0;
}

