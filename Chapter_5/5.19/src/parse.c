#include "declaration.h"
#include <string.h>

void encapsulate_token(char *, char *);
void move_asterisk_or_name(char *, char *, int);
void check_missing_elements(void);

/*an awfully complicated function parse() deals with everything that comes in our way */
int parse(void)
{
    int type = 0;
    extern int tokentype, asterisk, comma, list, encapsulate;
    extern char token[MAXTOKEN], out[1000], datatype[MAXTOKEN], name[MAXTOKEN];
    char temp[MAXTOKEN] = {0}, tempbuf[MAXTOKEN * 10] = {0};

get_another_token:
    while (gettoken(NONE) != EOF) {
        if (tokentype == ERR) /* check if the 1st token is a name or not */
            print_error("error: the name should be at the beginning of a declaration\n", NONE);
        else if ((tokentype == '\n' || (!(tokentype & NAME) && tokentype != ',')))
            print_error("error: not enough parameters to process or wrong sequence.\n", NONE);
        else if (!*out)
            strcpy(out, token);
        else
            strcat(out, token);
        memset(token, 0, sizeof(token));
        while ((type = gettoken(NONE)) != '\n' && type != EOF) {
            if (type == ')') {
                encapsulate = FALSE;
                check_missing_elements();
                continue;
            }
            if (type == '(' || type == ',') {
                memset(token, 0, sizeof(token));
                goto get_another_token;
            }
            if (type == ERR)
                print_error("error: unknown error.\n", NONE);
            else if (type == PARENS || type & BRACKETS) {
                strcat(out, token);
                memset(token, 0, sizeof(token));
                if (type & COMMA) {
                    strcat(out, ", ");
                    if (encapsulate == TRUE) {
                        memset(token, 0, sizeof(token));
                        continue;
                    }
                    goto get_another_token;
                }
            }
            else if (type & ASTERISK) {
                memset(temp, 0, sizeof(temp));
                if (type & ENCAP_TOKEN)
                    encapsulate_token(temp, tempbuf);
                else {
                        while (--asterisk >= 0) strcat(temp,"*");
                        move_asterisk_or_name(temp, tempbuf, NONE);
                        clear_buffers(temp, token, tempbuf, NULL, NULL, NULL, &asterisk);
                }
            } else if (type & NAME) {
                move_asterisk_or_name(temp, tempbuf, NAME);
                clear_buffers(temp, token, tempbuf, NULL, NULL, NULL, &asterisk);
            } else
                print_error("error: invalid input.\n", NONE);
        }
        if (type == EOF) return 0;
        printf("%s;  ==> OK\n", out);
        clear_buffers(temp, token, tempbuf, datatype, out, name, &asterisk);
        tokentype = encapsulate = list = comma = 0; 
    }
    return 0;
}

void clear_buffers(char *buf1, char *buf2, char *buf3, char *buf4, char *buf5, char * buf6, int *asterisk)
{
    memset(buf1, 0, MAXTOKEN);
    memset(buf2, 0, MAXTOKEN);
    memset(buf3, 0, MAXTOKEN * 10);
    if (buf4)
        memset(buf4, 0, MAXTOKEN);
    if (buf5)
        memset(buf5, 0, MAXTOKEN * 10);
    if (buf6)
        memset(buf6, 0, MAXTOKEN);
    if (asterisk)
        *asterisk^=*asterisk;
}

void encapsulate_token(char *temp, char *tempbuf)
{
    extern int asterisk, encapsulate;
    extern char out[];
    strcat(temp, "(");
    while (--asterisk >= 0)
        strcat(temp,"*");
    strcpy(tempbuf, &out[strlen(out) - 1]);
    strcat(temp, tempbuf);
    strcat(temp, ")");
    if (strstr(out, ","))
        out[strlen(out) - 1] = '\0';
    if (*out == '(' && *temp != '*') {
        if (out[strlen(out) - 1] != '(')
            strcpy(&out[strlen(out) - 1], temp);
        else
            strcat(out, temp);
    } else {
        if (encapsulate == FALSE) {
            if (strstr(out, ","))
                strcat(out, temp);
            else
                strcpy(out, temp);
        } else {
            if (strstr(temp, ","))
                strcpy(out, temp);
            else
                strcpy(&out[strlen(out) - 1], temp);
        }
    }

}

void move_asterisk_or_name(char * temp, char *tempbuf, int type)
{
    extern int encapsulate;
    extern char out[], token[];
    int len = 0;

    if (type & NAME) {
        if (encapsulate == TRUE) {
            for (len = strlen(out) - 1; out[len] != ',' && out[len] != '('; len--) ;
            if (out[len] == '(' && (out[len - 1] == ' ' || out[len - 1] == '*'))
                while(out[--len] != '(' && out[len] != ',' && out[len] == '*') ;
            if (out[len + 1] == '*' && out[len + 2] == '(') len++;
            strcpy(tempbuf[0] == '('? &tempbuf[1] : tempbuf, out[len] == ',' ? out[len + 1] == '*' ? &out[len + 1] : &out[len + 2]: out[len - 1] == '(' ? &out[len] : (out[len] == '(' || out[len] == '*') && out[len - 1] == ',' ? &out[len] : &out[len + 1]);
            sprintf(out[len] == ',' ? &out[len + 1] : out[len - 1] == '(' || out[len - 1] == ',' || out[len - 1] == '*' ? &out[len] : &out[len + 1],"%s %s", token, tempbuf);
        } else {
            sprintf(temp, "%s %s", token, out);
            strcpy(out, temp);
        }
    } else {
        if (encapsulate == TRUE) { /* move asterisk inside the function at the beginning or after a comma in a list */
            for (len = strlen(out) - 1; out[len] != ',' && out[len] != '('; len--) ;
            if (out[len] == '(' && (out[len - 1] == '(' || out[len - 1] == ',')) tempbuf[0] = '(';
            strcpy(tempbuf[0] == '(' ? &tempbuf[1] : &tempbuf[0], out[len] == ',' ? &out[len + 2] :  &out[len + 1]);
            if (type == NONE)
                sprintf(out[len] == ',' ? &out[len + 1] : tempbuf[0] == '(' ? &out[len] : &out[len + 1],"%s%s", temp, tempbuf);
            else
                sprintf(out[len] == ',' ? &out[len + 1] : tempbuf[0] == '(' ? &out[len] : &out[len + 1],"%s %s", temp, tempbuf);
        } else { /* move the asterisk at the beginning of the decl */
            strcat(temp, out);
            strcpy(out, temp);
        }
    }
}

void check_missing_elements(void)
{
    char tempbuf[MAXTOKEN * 10] = {0};
    char buff[MAXTOKEN] = {0};
    char *ptr = NULL;
    extern char out[];
    int i, j;

    sprintf(tempbuf, "%s", out);
    if (!(ptr = strstr(tempbuf, ")(")) && !(ptr = strstr(tempbuf, "(")))
        print_error("error: unknown error.\n", NONE);
    if (*ptr++ == ')')
        ptr++;
    sprintf(tempbuf, "%s", ptr);
    ptr = strtok(tempbuf, ",");
    do {
        j = -1, i = -1;
        do {
            ++i, ++j;
            if (i == 0 && ptr[i] == ' ') i++;
            buff[j] = ptr[i];
        } while(ptr[i]!= ' ' && ptr[i] != ' ' && ptr[i] != '[' && ptr[i] != '(' && ptr[i] != '*');
        buff[j] = '\0';
        if (type_name_check(buff) != TYPE)
            print_error("error: you may have forgotten type in one of the function parameters\n", NONE);
    } while ((ptr = strtok(NULL, ",")));
}
