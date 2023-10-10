#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

typedef unsigned char u_char;
typedef unsigned int u_int;
typedef u_char * StringP;
void check_endianess(void);
#define PRINT_BORDER() printf("--------------------------------------\n");
#define DISPLAY_LITTLE_ENDIAN_BYTE_ORDER(arg) printf(">>> Little-endian representation <<<\nreg.dword=0x%x\n", arg.dword); \
                                              printf("the 1st byte1=0x%x; byte2=0x%x; byte3=0x%x; byte4=0x%x\n", arg.bytes.byte1, arg.bytes.byte2, arg.bytes.byte3, arg.bytes.byte4);
#define CONVERT_LITTLE_ENDIAN_TO_BIG_ENDIAN(arg) htonl(arg.dword);
#define DISPLAY_BIG_ENDIAN(arg1, arg2) printf(" >>> Big-endian representation <<< \nval=0x%x\n", arg1); \
                                printf("the 1st byte is 0x12 now.\n"); \
                                arg2 = (u_char *) &arg1; \
                                printf("byte1=0x%x\n", *arg2); \
                                *arg2+=1; \
                                printf("byte1=0x%x(incremented), byte2=0x%x, byte3=0x%x, byte4=0x%x\n", *arg2, *(arg2 + 1), *(arg2 + 2), *(arg2 + 3)); \
                                *(arg2 + 3)-=1; \
                                printf("byte1=0x%x, byte2=0x%x, byte3=0x%x, byte4=0x%x(decremented)\n", *arg2, *(arg2 + 1), *(arg2 + 2), *(arg2 + 3)); \
                                printf("val=0x%x (big endian)\n", arg1);
#define REPLACE_1ST_BYTE_OF(arg, new_val) arg.bytes.byte1 = new_val; // 0x78 > 0x79 in little-endian arch
void check_endianess(void)
{
    u_int what_endianess = 0xFF00;
    char *bytep = (char *) &what_endianess;
    *bytep ? printf("the machine is big-endian.\n") : printf("the machine is little-endian.\n");
}

typedef union HW_reg {
    struct {
        u_char byte1; // 0x78 --> little-endian 0x12 --> big-endian
        u_char byte2; // 0x56                   0x34
        u_char byte3; // 0x34                   0x56
        u_char byte4; // 0x12                   0x78
    } bytes;
    u_int dword;
} HW_reg;

int main(void)
{
    HW_reg reg;
    u_int val;
    reg.dword = 0x12345678;
    StringP bytep = NULL;
    check_endianess();

    PRINT_BORDER();
    DISPLAY_LITTLE_ENDIAN_BYTE_ORDER(reg);
    REPLACE_1ST_BYTE_OF(reg, 0x79);
    DISPLAY_LITTLE_ENDIAN_BYTE_ORDER(reg);
    PRINT_BORDER();

    PRINT_BORDER();
    val = CONVERT_LITTLE_ENDIAN_TO_BIG_ENDIAN(reg);
    DISPLAY_BIG_ENDIAN(val, bytep);
    PRINT_BORDER();

    return EXIT_SUCCESS;
}
