#include <stdio.h>
#include <string.h>

#define MAXLINES 5000 // max number of lines being sorted 
#define ALLOCSIZE 1000
#define MAXLEN 1000

char *lineptr[MAXLINES]; //array of pointers;
char len = 0;

int readlines (char *[], char *, int);
void writelines (char *[], int);
void qsort (char *[], int, int);
char *get_line (char *, int);

/*
Rewrite readlines to store lines in an array supplied by main, rather than calling alloc to maintain storage. How much faster is the program?
input:  
Hello!
Amarth
Freedom
BDSM
output:
Amarth
BDSM
Freedom!
Hello!
*/

int main (void)
{
    char array_lines[MAXLEN];
    int nlines = 0; //the number of lines inserted
    if ((nlines = readlines (lineptr, array_lines, MAXLINES)) >= 0)
    {
        printf("\nsymbol in array: %c\n", *lineptr[0]);
        printf("7) pre-qsorted line: %s\n", *lineptr);
        qsort (lineptr, 0, nlines - 1);

        printf("8) qsorted line: %s\n", *lineptr);
        writelines (lineptr, nlines);
        return 0;
    }
    else
    {
        printf("error: input too big to sort\n");
        return 1;
    }
}

void qsort (char *v[], int left, int right)
{
    /*
    when just initialized:
    Hello!
    Amarth
    Freedom
    BDSM
    length = 0 - 3;
    */
    int i = 0;
    int last = 0;
    void swap (char *v[], int i, int j);

    if (left >= right)
    {
        return;
    }

    swap (v, left, ((left + right) / 2)); // 3/2 = 1 (Amarth)
    //swap 0 (Hello) and 1 (Amarth)
    /*
    after the 1st swap:
    Amarth
    Hello!
    Freedom
    BDSM
    */
    /*
    //swap 1 (Hello!) and swap 1 (Hello!)
    after the right-sided swap:

    */
    last = left; //last contains 0 (Amarth)
    // after the right-sided swap contains : 1 (Hello!)

    for (i = left + 1; i <= right; i++)
    {
           /*       
           i = 1    i = 2
           ({Amarth}) ({Hello}) {} - pivot element
           [Hello!] [Freedom]   () - the LAST position for pivot to be put
           Freedom  BDSM        [] - current position in an array
           BDSM     i = 3
           *///     Hello
           /*       (Freedom)
           i = 2    [BDSM]
           (Amarth)  i = 3
           Hello!    {Hello} > BDSM  
           [Freedom] Freedom > Freedom
           BDSM      (BDSM)  > {Hello}
           */
           /*
           i = 3
           (Amarth)
           Hello!
           Freedom
           [BDSM]
           */
        if ((strcmp(v[i], v[left])) < 0)
        // is (v[1](Hello!), v[0] (Amarth)) less than 0 ?
        // NO, becasue 7 is greater than 0
        // fals condition, ignore the body of if

        // is (v[2](Freedom), v[0] (Amarth)) less than 0 ?
        // NO, becasue 5 is greater than 0
        // fals condition, ignore the body of if

        // is (v[3](BDSM), v[0] (Amarth)) less than 0 ?
        // NO, becasue 1 is greater than 0
        // fals condition, ignore the body of if

        // is (v[2](Freedom), v[1] (Hello)) less than 0 ?
        // YES, becasue -2 is less than 0
        // true condition, go to the body of if

        // is (v[3](BDSM), v[2] (FREEDOM)) less than 0 ?
        // YES, becasue -4 is less than 0
        // true condition, go to the body of if
        {
            swap(v, ++last, i);
            //swap (2, 2), i.e (Freedom) and (Freedom)
            //last is 2 (Freedom)
            //swap(3, 3), i.e (BDSM) and (BDSM)
            //last is 3 (BDSM)
        }   
    }
    
    swap (v, left, last);
    // swap (0, 0) or v[left] and v[last] to return last (Amarth) 
    //to the appointed position;
    //as of now, the current situation is:
    /*
    Amarth  
    Hello!
    Freedom
    BDSM 
    */
    // swap(1, 3) or Hello and BDSM to return last = BDSM
    // to the appointed position
    /*
    BDSM
    Freedom
    Hello!
    */
    qsort(v, left, last - 1);
    //qsort the left-sided part of array
    //nothing to be qsorted, because
    //left (0) is greater than -1
    //BDSM and Freedom will be qsorted
    //but nothing will happen, because
    //BDSM and BDSM are equal, nothing to swap
    qsort(v, last + 1, right); // 1 - 3
    //qsort the right-sided part of array
    // Hello!  > BDSM   
    // Freedom > Freedom
    // BDSM    > Hello! 
    // nothing to sort, becasue 4 > 3
    // nothing to sort 
}

void writelines (char *lineptr[], int nlines) // output lines
{
    printf("9) sorted lines:\n");
    while (nlines-- > 0)
    {
        printf("%s\n", *lineptr++);
    }
}
int readlines (char *lineptr[], char *array, int maxlines)
{
    extern char len;
    int nlines = 0;
    char *p = NULL;
    int mark = 0;

    while ((p = get_line(array, MAXLEN)) != 0 && *(p + len) == '\0')
    {
        printf("2) the first symbol: %c\n", *(p));
        printf("3) the line at pointer: %s", p);

        if (nlines >= maxlines || p == NULL )
        {
            return -1;
        }
        else
        {
            if (*(p + len - 1) == '\n')
            {
                *(p + len - 1) = '\0';
            }
            else if (*(p + len) == '\0')
            {
                *(p + len) = '\0';
                mark = 1;
                printf("\n4) mark of EOF: %d\n", mark);
            } 
             
            lineptr[nlines++] = p;
            array += len;
            len = 0;
            if (mark)
            {
                break;
            }
        }
        printf("5) current number of lines : %d\n", nlines);
    }
    printf("5) current number of lines : %d\n", nlines);
    printf("6) finished line %s %s %s\n", lineptr[0], lineptr[1], lineptr[3]);
    return nlines;
}
char *get_line(char *charline, int maxlen) 
{
    int c = 0;
    extern char len;

    for (; --maxlen > 0 && (c = getchar()) != EOF && c!= '\n';)
    {
        *charline++ = c;
        len++;
    }
    if (c == '\n')
    {
        *charline++ = c;
        len++;
        *charline = '\0';
    }
    if(c == EOF)
    {
       *charline = '\0';
    }
    printf("0) the length of line including '\\n' : %d\n", len);
    
   printf("1) in get_line : %s", charline - len);

    return charline - len;
}
void swap (char *v[], int i, int j)
{
    char *temp;
    temp = v[i]; // Hello       //Amarth
    v[i] = v[j]; // 0 - Amarth  //Amarth
    v[j] = temp; // 1 - Hello   //Amarth
}