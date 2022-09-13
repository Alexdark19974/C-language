#ifndef IOB_H_
#define IOB_H_
#include "syscalls.h"

File _iob[OPEN_MAX] =
{
	{
		0,
		(char *) NULL,
		(char *) NULL,
		_READ /*| _UNBUF*/,
		0
	},

	{
		0,
		(char *) NULL,
		(char *) NULL,
		_WRITE /*| _UNBUF*/,
		1
	},

	{
		0,
		(char *) NULL,
		(char *) NULL,
		_WRITE | _UNBUF,
		2
	}
};
#endif
