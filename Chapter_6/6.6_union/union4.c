#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char u_char;
typedef char * StringP;
typedef union {
    struct {
        u_char b1: 1;
        u_char b2: 1;
        u_char b3: 1;
        u_char b4: 1;
        u_char reserved:4;
    } bits;
    u_char byte;
} HW_RegisterB;
StringP check_endianness(void);
#define ON  1
#define OFF 0
#define PRINT_ENDIANNESS() check_endianness()
#define SIZE_OF(arg) sizeof(arg)
#define DISPLAY_BYTE_AND_BITS(reg) printf("byte=%u, bit1: %u, bit2:%u, bit3:%u, bit4:%u, reserved=%u\n", reg.byte, reg.bits.b1, reg.bits.b2, reg.bits.b3, reg.bits.b4, reg.bits.reserved)
#define ASSIGN_VAL_TO_BYTE(arg, val) arg.byte = val
#define ACTIVATE_BIT(reg, bit) if (bit == 1) reg.bits.b1 = ON; \
                               else if (bit == 2) reg.bits.b2 = ON; \
                               else if (bit == 3) reg.bits.b3 = ON; \
                               else if (bit == 4) reg.bits.b4 = ON; \
                               else return printf("unknown bit number (%u)", bit);
#define DEACTIVATE_BIT(reg, bit) if (bit == 1) reg.bits.b1 = OFF; \
                                      else if (bit == 2) reg.bits.b2 = OFF; \
                                      else if (bit == 3) reg.bits.b3 = OFF; \
                                      else if (bit == 4) reg.bits.b4 = OFF; \
                                      else return printf("unknown bit number (%u)", bit);
int main(void)
{
    HW_RegisterB reg;
    printf("The arch is %s\n", PRINT_ENDIANNESS());
    printf("Size of union HW_RegisterB is =%ld", SIZE_OF(reg));

    ASSIGN_VAL_TO_BYTE(reg, 2);

    DISPLAY_BYTE_AND_BITS(reg);

    ACTIVATE_BIT(reg, 1);

    DISPLAY_BYTE_AND_BITS(reg);

    DEACTIVATE_BIT(reg, 1);

    DISPLAY_BYTE_AND_BITS(reg);


    return EXIT_SUCCESS;
}

StringP check_endianness(void)
{
    u_int what_endianness = 0xFF00;
    char *bytep = (char *) &what_endianness;
    return *bytep ? "big-endian.\n" : "little-endian.\n";
}
