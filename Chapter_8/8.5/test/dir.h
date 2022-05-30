#ifndef DIRSIZ
#define DIRSIZ 14

struct direct	/* запись в каталоге */
{
	ino_t d_ino;		 /*номер индекса*/
	char d_name[DIRSIZ]; /* в длинном имени нет '\0' */
};
#endif
