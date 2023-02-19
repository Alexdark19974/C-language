#include "linesort.h"

/* qsort:  sort v[left]...v[right] into increasing order */
void qsort(char *v[], int left, int right)
{
#if !defined ALTERNATESORT
    int i, last;
    void swap(char *v[], int i, int j);
    if (left >= right)    /* do nothing if array contains */
        return;           /* fewer than two elements */
    swap(v ,left, (left + right)/2);
    last = left;
    for(i = left + 1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v ,left, last);
    qsort(v, left, last-1);
    qsort(v , last+1, right);
#else
    if (left < 0 || !right || left >= right)
        return;
    int pivot = (left + right) / 2;
    int i = 0, j = 0;
    i = left - 1;
    j = right + 2;

    do {
        i++;
    } while (strcmp(v[i], v[pivot]) < 0);

    do {
        j--;
    } while (strcmp(v[j], v[pivot]) > 0);
    swap(v, i, j);
    qsort(v, left, pivot);
    qsort(v, pivot + 1, right);
#endif
}

/* swap:  interchange v[i] and v[j] */
void swap(char *v[], int i, int j)
{
    char *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
