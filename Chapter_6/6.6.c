#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASHSIZE 101
#define CHARLIMIT 1000
#define BUF_SIZE 100
#define CLEANUPSIZE 1000
#define NO -1
#define YES 0
#define PREPROCESSOR '#'
#define AUTO 'A'
#define MANUAL '1'

struct nlist /*запись таблицы*/
{
    struct nlist *next; /*следующая запись в цепочке, указывает на N-элемент в хеш-таблице, определенный хеш-функцией */
    char *name; /* имя в #define */
    char *defn;/* подставляемый текст */
};

struct key_value
{
    char *key;
    char *value;
};

struct prohibit_list
{
	char *element;
};

static struct nlist *hashtab[HASHSIZE] = {NULL}; /*таблица указателей, каждый элемент указывает на начало элемента списка struct nlist *np */
int hashtab_collector[CLEANUPSIZE] = {0};
int hashtab_collector_counter = 0;
char *my_strdup_collector[CLEANUPSIZE] = {NULL};
int my_strdup_collector_counter = 0;
struct nlist *next_collector[CLEANUPSIZE] = {NULL};
int next_collector_counter = 0;
char buf[BUF_SIZE] = {0};
int bufp = 0;

unsigned int hash(char *);
struct nlist *lookup(char *);
char *my_strdup(char *);
struct nlist *install(char *, char *);
int get_line(struct key_value *, int);
void hash_table(void);
int my_delete(void);
void free_memory(void);
void example(void);
void start(char);
int check(char *);

int main(void)
{
	hash_table();
	free_memory();
    return 0;
}

struct nlist *install(char *name, char *defn)
{
	struct nlist *np = NULL;
	unsigned hashval = 0;

	if ((np = lookup(name)) == NULL)
	{
		np = (struct nlist *) malloc(sizeof(*np));

		if (np == NULL || (np->name = my_strdup(name)) == NULL)
		{
			return NULL;
		}

		hashval = hash(name);
		hashtab_collector[hashtab_collector_counter] = hashval;
		hashtab_collector_counter++;
		np->next = hashtab[hashval];  // указывает на указательный элемент в таблице указателей, изначально 0x0, то есть он ни на что не указывает,

		if (np->next != NULL)
		{
			 next_collector[next_collector_counter] = np->next;
			 next_collector_counter++;
		}
									 //в последствии, будет хранить старый указатель на предыдущую структуру, сцепляя их друг с другом
		hashtab[hashval] = np; 		// указательный элемент таблицы указателей  указывает на указатель на структуру, теперь уже не 0x0
		puts("Succesfully added");
	}
	else
	{
		free((void *) np->defn);
		puts("successfully replaced");
	}

	if ((np->defn = my_strdup(defn)) == NULL)
	{
		return NULL;
	}

	return np;
}

/*lookup: поиск элемента s  в таблице hashtab*/
struct nlist *lookup(char *s)
{
    struct nlist *np = NULL;

	int n = hash(s);

	for (np = hashtab[n]; np != NULL; np = np->next)
	{
		if (np->name != NULL && strcmp(s, np->name) == 0)
		{
		    printf("Element to be replaced: hash is %d, key is %s, value is %s\n", n, np->name, np->defn);
			return np; /*элемент найден*/
		}
	}

	return NULL; /*элемент не найден*/
}

unsigned int hash(char *s)
{
    unsigned int  hashval = 0;

    for (hashval = 0; *s != '\0'; s++)
    {
        hashval = *s + 31 * hashval;
    }

    return hashval % HASHSIZE;
}

int get_line (struct key_value *k_v, int limit)
{
    int c = 0;
    char *tmp_w = (char *) malloc(CHARLIMIT);
    char *tmp_w_ptr = tmp_w;
    int getch();
    void ungetch(int);

    while (isspace(c = getch()) || c == ',' || c == '\n' || c == ';' || c == '.' || c == '+')
    {
        ;
    }

    if (c != EOF)
    {
        *tmp_w_ptr = c;
        tmp_w_ptr++;
    }
    else if (c == EOF)
    {
		free(tmp_w);
    	tmp_w_ptr = NULL;
		return EOF;
    }

    for (; --limit > 0; tmp_w_ptr++)
    {
        if (!isalnum(*tmp_w_ptr = c = getch()) &&  *tmp_w_ptr != '#' && *tmp_w_ptr != '<' && *tmp_w_ptr != '>' && *tmp_w_ptr != ')'
			&& *tmp_w_ptr  != '(' && *tmp_w_ptr != '.' && *tmp_w_ptr != '{' && *tmp_w_ptr != '}' && *tmp_w_ptr != '+' && *tmp_w_ptr != '=' && *tmp_w_ptr != '_')
        {
            ungetch (*tmp_w_ptr);
            break;
        }
    }

    *tmp_w_ptr = '\0';

    if (k_v->key == NULL)
    {
        k_v->key = my_strdup(tmp_w);
    }
    else
    {
        k_v->value = my_strdup(tmp_w);
    }

    free(tmp_w);
    tmp_w_ptr = NULL;

    return 0;
}

char *my_strdup(char *s) /*creating a copy of string 's'*/
{
    char *p = NULL;
    int length = strlen(s);

    p = (char *) malloc(length + 1); /*+1 for '\0'*/

	my_strdup_collector[my_strdup_collector_counter] = p;
	my_strdup_collector_counter++;

    if (p != NULL)
    {
        strncpy(p, s, length);
        p[length] = '\0';
    }

    return p;
}

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUF_SIZE)
    {
        printf("ungetch: too many characters\n");
    }
    else
    {
        buf[bufp] = c;
        bufp++;
    }
}


void hash_table(void)
{
	enum { EXAMPLE = 0, MANUAL_START, UNDEF, END };
    char instr = 0;
	char flag = 0;

    printf("\n>>>>>Welcome to Hashtable<<<<<\n");

    printf("Press 1 and push enter to get going ----- press 0 to look at an example of what you should do\n");

    printf("Enter the command: ");

	while ((instr = getchar()) != EOF)
	{
		if (instr != PREPROCESSOR)
		{
			if (!isalpha(instr))
			{
				char c = 0;

				if ((c = getch()) != '\n')
				{
					ungetch(instr);
					ungetch(c);
					instr = AUTO;
				}
				else
				{
					ungetch(c);
					instr-= 48;
				}
			}
		}
		switch (instr)
		{
			case EXAMPLE:
			{

				example();

				break;
			}
			case PREPROCESSOR:
			{
				ungetch(instr);

				flag = PREPROCESSOR;
				start(flag);

				break;
			}
			case AUTO:
			{
				start(flag);
				break;
			}
			case MANUAL_START:
			{
				flag = MANUAL;
				start(flag);

				break;
			}
			case UNDEF:
			{
				getchar();

				int status = my_delete();

				if (status == NO)
				{
					puts("name not found");
				}
				else
				{
					puts("successfully deleted");
				}

				break;
			}
			case END:
			{
				puts("terminating the programm. Goodbye.");
				return;
			}
			default:
			{
				puts("Invalid command");

				getchar();

				break;
			}
		}

		printf("Enter the command: ");
	}

    puts("terminating the programm. Goodbye.");
}

int my_delete(void)
{
	struct key_value del_key = {NULL, NULL};
	struct nlist *np = NULL;
	unsigned int hashval = 0;

	puts("deleting...");

	printf("Enter the key to delete the key and the value: ");

	get_line(&del_key, CHARLIMIT);

	hashval = hash(del_key.key);

	for (np = hashtab[hashval]; np != NULL ; np = np->next)
	{
		if (strcmp(hashtab[hashval]->name, del_key.key) == 0)
		{
			hashtab[hashval]->name = NULL;
			hashtab[hashval]->defn = NULL;
			return YES;
		}
	}

	return NO;
}

void free_memory(void)
{
	for (int i = 0; i != my_strdup_collector_counter; i++)
    {
    	if (isalnum(*my_strdup_collector[i]) || *my_strdup_collector[i] == '#' || *my_strdup_collector[i] == '<' || *my_strdup_collector[i] == '{' || *my_strdup_collector[i] == '}'
			|| *my_strdup_collector[i] == '=')
        {
            free(my_strdup_collector[i]);
            my_strdup_collector[i] = NULL;
        }
    }

	for (int i = 0; i != next_collector_counter; i++)
	{
		free(next_collector[i]);
		next_collector[i] = NULL;
	}

    for (int i = 0; i != hashtab_collector_counter; i++)
    {
        if (hashtab[hashtab_collector[i]] != NULL)
        {
            free(hashtab[hashtab_collector[i]]);
            hashtab[hashtab_collector[i]] = NULL;
        }
    }
}

void example(void)
{
	puts("---Enter the key as a string of chars, then press SPACE, then enter the value as a string of chars");
    puts("--------Example: Stalin 666");
    puts("------------1)If you want to exit the hashtable, enter \"exit\" and press ENTER");
    puts("----------------2) If you want to terminate the program, press 3 and push \"ENTER\"");
    puts("---------------------3) If you want to delete a key and a value, press 2 and push \"ENTER\"");
}

void start (char flag)
{
	struct key_value k_v = {NULL, NULL};
	struct nlist *cond_ptr = NULL;

	printf("Enter the key and the value: ");

	while (get_line(&k_v, CHARLIMIT) != EOF)
    {
		if (flag == MANUAL)
		{
			if (strcmp(k_v.key, "exit") == 0)
			{
            	puts("exiting the hashmap");
            	k_v.key = NULL;
            	break;
        	}

		}
		if (flag == PREPROCESSOR)
		{

			int res = check(k_v.key);

			if (res == NO)
			{
				k_v.key = NULL;
				continue;
			}
			else
			{
				k_v.key = NULL;
				get_line(&k_v, CHARLIMIT);
				get_line(&k_v, CHARLIMIT);
			}
		}

        if (k_v.value == NULL)
        {
            continue;
        }
        else
        {
            if ((cond_ptr = install(k_v.key, k_v.value)) == NULL)
            {
                puts("no space in lookup table");
                exit(-1);
           	}

            k_v.key = NULL;
            k_v.value = NULL;
        }

		printf("Enter the key and the value: ");
    }
}

int check(char *s)
{
	static struct prohibit_list array[] =
    {
		{"#include"},
		{"<stdlib.h>"},
        {"<stdio.h>"},
        {"int"},
		{"main"},
		{"void"},
		{"main(void)"},
        {"return"},
        {"double"},
        {"float"},
        {"static"},
        {"const"},
		{"{"},
		{"}"},
		{"="},
		{"+"},
		{";"},
        {NULL},
	};

	for (int i = 0; array[i].element != NULL; i++)
	{
		if (strcmp(s, array[i].element) == 0)
		{
			return NO;
		}
		else if (strcmp(s, "#define") == 0)
		{
			return YES;
		}
	}

	return NO;
}
