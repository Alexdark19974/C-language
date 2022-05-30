#ifndef DIRENT_H
#define DIRENT_H
#define MYNAME_MAX 14 /* самая длинная компонента времени */
							  /* системно-зависимая */

typedef struct 			/* Универсальный пункт списка */
{
	long ino;		   			/* номер индекса */
	char name[MYNAME_MAX + 1];	/* имя + '\0' */
} Dirent;

typedef struct
{					/* минимум: без буферизации и т.п. */
	int fd;				/* файловый дескриптор каталога */
	Dirent d; 			/* пункт списка файлов */
} Dir;


DIR *myopendir(char *dirname);
struct dirent *myreaddir(DIR *dfd);
void myclosedir(DIR *dfd);

#endif
