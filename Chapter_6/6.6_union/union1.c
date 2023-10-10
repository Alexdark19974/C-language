#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <arpa/inet.h>

typedef char * StringP;
typedef unsigned int u_int;

typedef union u_Tag {
    unsigned char c_val;
    int i_val;
    float f_val;
    StringP str_val;
} u_Tag, *uTagP;

struct test {
    char val1[5];
    int val2;
} test;

void example_1(uTagP);
void example_2(uTagP);
void example_3(uTagP);

#define PRINT_BORDER() printf("--------------------------------------\n");
#define ALLOCATE_MEMORY(arg) if ((arg = calloc(1, sizeof(*arg))) == NULL) { \
                                perror("malloc"); \
                                exit(EXIT_FAILURE); \
                             }
#define FREE_MEMORY(arg) free(arg->str_val); free(arg); arg = NULL;
#define EXPLAIN_ENDIANNESS(arg) printf("As soon as we allocate memory for \"string\", the variables in the u_tag union will contain bytes of the address that str_val points to.\n"); \
                                arg->str_val = strdup("string"); \
                                printf("tagp->c_val=%x -> 1 left-most inisignificant byte (little-endian)\n" \
                                        "arg->i_val=%x -> 4 left-most insignificant bytes -> little-endian with big-endian display\n" \
                                        "arg->f_val=%f\ntagp->str_val=%s\ntag_str_val=%p\n", arg->c_val, arg->i_val, arg->f_val, arg->str_val, arg->str_val); \
                                printf("How it actually looks depending on the little-endian architecture:\n"); \
                                ptr = (StringP) &arg->i_val; \
                                for (i = 0; i < sizeof(u_int); i++) \
                                    printf("ptr to byte %d = %x; ", i + 1, (u_char) *ptr++); \
                                putchar('\n'); \
                                printf("To make sure that tagp->i_val is, indeed, little-endian, we will convert it.\n"); \
                                check_endianess(); \
                                printf("before: tagp->i_val=%x\n", arg->i_val); \
                                val = ntohl(arg->i_val); \
                                printf("after: tagp->i_val=%x\n", val);

void check_endianess(void)
{
    u_int what_endianess = 0xFF00;
    char *bytep = (char *) &what_endianess;
    *bytep ? printf("the machine is big-endian.\n") : printf("the machine is little-endian.\n");
}

void explain_struct_union_diff(uTagP tagp)
{
    printf("(union) sizeof(*tagp)=%ld -> each union field shares the same memory area;\n", sizeof(*tagp));
    printf("whereas (struct) sizeof(test)=%ld enables each field to have their own memory area\n\n", sizeof(struct test));
    printf("even if sizeof(test.val1)=%ld, sizeof(test.val2) = %ld\n", sizeof(test.val1), sizeof(test.val2));
    printf(", 2 additional bytes are padded to achieve contiguous memory area.\n");
    printf("something like this: |0x1, 0x2, 0x0, 0x0, 0x5|\n"); 
    printf("all fields must be divisible by the largest field in the structure, which is \"sizeof(test.val2)= %ld\"\n", sizeof(test.val2));
}

void example_1(uTagP tagp)
{
    printf("Example 1:\n");
    tagp->c_val = 1;
    printf("tagp->c_val=%u\ntagp->i_val=%u\ntagp->f_val=%f -> floating numbers are a mess due to the mantiss and the exponent stuff\n", tagp->c_val, tagp->i_val, tagp->f_val);
    PRINT_BORDER();
}

void example_2(uTagP tagp)
{
    PRINT_BORDER();
    printf("Example 2:\n");
    tagp->i_val = 123;
    printf("tagp->c_val=%u\ntagp->i_val=%u\ntagp->f_val=%f\n", tagp->c_val, tagp->i_val, tagp->f_val);
    PRINT_BORDER();
}

void example_3(uTagP tagp)
{
    PRINT_BORDER();
    printf("Example 3:\n");
    tagp->f_val = 666.6;
    printf("tagp->c_val=%u\ntagp->i_val=%u\ntagp->f_val=%f\n", tagp->c_val, tagp->i_val, tagp->f_val);
    PRINT_BORDER();
}

void union_explain(void)
{
    uTagP tagp = NULL;
    u_int val = 0, i;
    StringP ptr = NULL;

    ALLOCATE_MEMORY(tagp);

    PRINT_BORDER();
    {
        explain_struct_union_diff(tagp);
        example_1(tagp);
        example_2(tagp);
        example_3(tagp);
        EXPLAIN_ENDIANNESS(tagp);
        FREE_MEMORY(tagp);
    }
    PRINT_BORDER();
}

int main(void)
{
    union_explain();

    return EXIT_SUCCESS;
}
