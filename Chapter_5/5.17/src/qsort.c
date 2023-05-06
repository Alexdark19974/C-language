#include "linesort.h"

/* qsort:  sort v[left]...v[right] into increasing order */
void _qsort(void *v[], int left, int right, int (*comp)(void *, void *, int, enum opt), enum opt opt, int field_length)
{
    void swap(void *v[], int i, int j);
    int i, last;
    if (left >= right)    /* do nothing if array contains */
        return;           /* fewer than two elements */
    if (_strcmp_ext((char *) v[left], (char *) v[(left + right) / 2], field_length, opt))
        swap(v ,left, (left + right)/2);
    last = left;
    for(i = left + 1; i <= right; i++)
        if ((opt & REVERSE) ? (_strcmp_ext(v[i], v[left], field_length, opt) > 0) : (_strcmp_ext(v[i], v[left], field_length, opt) < 0)) {
            swap(v, ++last, i);
        }
    swap(v ,left, last);
    _qsort(v, left, last- 1, comp, opt, field_length);
    _qsort(v , last+1, right, comp, opt, field_length);
}

/* swap:  interchange v[i] and v[j] */
void swap(void *v[], int i, int j)
{
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

