#include "linesort.h"

/* qsort:  sort v[left]...v[right] into increasing order */
void _qsort(void *v[], int left, int right, int (*comp)(void *, void *, enum opt), enum opt opt)
{
    void swap(void *v[], int i, int j);
    int i, last;
    if (left >= right)    /* do nothing if array contains */
        return;           /* fewer than two elements */
    if (_strcmp_ext((char *) v[left], (char *) v[(left + right) / 2], opt))
        swap(v ,left, (left + right)/2);
    last = left;
    for(i = left + 1; i <= right; i++)
        if ((opt & REVERSE) ? (_strcmp_ext(v[i], v[left], opt) > 0) : (_strcmp_ext(v[i], v[left], opt) < 0)) {
            if ((opt & DIRECTORY_ORDER) && last <= right && !isalnum(*((char *)v[last + 1])) && *((char *) v[last + 1]) != '\n')
                while (!isalnum(*((char *)v[last--])) && *((char *) v[last]) != ' ') ;
            swap(v, ++last, i);
        }
    swap(v ,left, last);
    _qsort(v, left, last- 1, comp, opt);
    _qsort(v , last+1, right, comp, opt);
}

/* swap:  interchange v[i] and v[j] */
void swap(void *v[], int i, int j)
{
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

