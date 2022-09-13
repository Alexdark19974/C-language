#ifndef IOB_H_
#define IOB_H_
#include "syscalls.h"

File _iob[OPEN_MAX] =
{
    {
        0,
        (char *) NULL,
        (char *) NULL,
		{ 1, 0, 0, }, //1 0 1
        0			// r w unbuf
    },

    {
        0,
        (char *) NULL,
        (char *) NULL,
        { 0, 1, 0, }, //0 1 1
        1			 //r w unbuf
    },

    {
        0,
        (char *) NULL,
        (char *) NULL,
        { 0, 1, 1, }, //0 1 1
        2				 //r w unbuf
    }
};
#endif
