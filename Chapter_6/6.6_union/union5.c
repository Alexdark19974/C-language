#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define ALLOCATE_MEMORY(bytes) malloc(bytes)
#define DISPLAY_LITTLE_ENDIANNESS(arg) printf("------------------ Little-endian representation ----------------\n"); \
                                       printf("The least significant bit is on the left.\n");\
                                       printf("byte1=%u, byte2=%u, byte3=%u, byte4=%u\n", *arg, *(arg + 1), *(arg + 2), *(arg + 3)); \
                                       printf("------------------ Little-endian representation ----------------\n");
#define DISPLAY_BIG_ENDIANNESS(arg) printf("------------------ Big-endian representation ----------------\n"); \
                                       printf("The least significant bit is on the left.\n");\
                                       printf("byte1=%u, byte2=%u, byte3=%u, byte4=%u\n", *arg, *(arg + 1), *(arg + 2), *(arg + 3)); \
                                       printf("------------------ Big-endian representation ----------------\n");
#define DISPLAY_TYPE_OF_ENDIANNESS(arg) printf("address=%s is in %s\n", arg, check_endianness());
typedef unsigned char u_char;
typedef unsigned int u_int;
typedef char * StringP;
StringP check_endianness(void);

typedef union {
    struct {
        u_char byte1;
        u_char byte2;
        u_char byte3;
        u_char byte4;
    } bytes;
    u_int addr;
} IpAddr;


int main(void)
{
    StringP ip_str = ALLOCATE_MEMORY(32);
    u_char *ptr = NULL;
    u_int val = 0;
    struct in_addr Addr;
    IpAddr ipv4Addr = {0};

    sprintf(ip_str, "%s", "192.168.0.1");

    DISPLAY_TYPE_OF_ENDIANNESS(ip_str);

    printf("Let's convert it into an unsigned integer and then suge char * pointer to prove the point.\n");

    val = inet_network(ip_str);
    ptr = (u_char *) &val;
    printf("Let's increment the right-most byte.\n");
    *(ptr + 3) += 1;

    DISPLAY_LITTLE_ENDIANNESS(ptr);

    printf("Now let's convert the little-endian value into the big endian one.\n");
    ipv4Addr.addr = (in_addr_t) inet_addr(ip_str);
    printf("And increment the right-most byte.\n");
    ipv4Addr.bytes.byte4++;

    Addr.s_addr = ipv4Addr.addr;
    ip_str = inet_ntoa((struct in_addr) Addr);
    ptr = (u_char *) &Addr.s_addr;

    DISPLAY_BIG_ENDIANNESS(ptr);

    val = ntohl(Addr.s_addr);
    printf("ntohl converts network byte order (big-endian) to host byte order (little-endian)=%u\n", val);
    ptr = (u_char *) &val;
    DISPLAY_LITTLE_ENDIANNESS(ptr);

    return EXIT_SUCCESS;
}

StringP check_endianness(void)
{
    u_int what_endianness = 0xFF00;
    char *bytep = (char *) &what_endianness;
    return *bytep ? "big-endian.\n" : "little-endian.\n";
}
